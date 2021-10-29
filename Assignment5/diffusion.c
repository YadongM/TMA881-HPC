#define _XOPEN_SOURCE 700

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
  
    int nmb_mpi_proc, mpi_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nmb_mpi_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

    int scatter_root = 0;

    int iter_num = 0;      // iteration number
    float diff_const = 0.; // diffusion constant
    // parsing arguments
    if (argc != 3)
    {
        fprintf(stderr, "Error: Wrong Syntax. Should be in form:\n./diffusion -n[number_of_iterations] -d[diffusion_constant]\n");
        exit(0);
    }
    char *ptr_n, *ptr_d;
    for (size_t ix = 1; ix < argc; ix++)
    {
        ptr_n = strchr(argv[ix], 'n');
        ptr_d = strchr(argv[ix], 'd');
        if (ptr_n)
            iter_num = strtol(++ptr_n, NULL, 10);
        else if (ptr_d)
            diff_const = strtof(++ptr_d, NULL);
    }

    // Read the input file
    int width = 0, height = 0; // the width and the height
    float *full_matrix = NULL;

    if (mpi_rank == scatter_root) {
        FILE *file;
        char line[100];
        char filename[] = "init";
        file = fopen(filename, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            exit(0);
        }

        fseek(file, 0, SEEK_SET); // to the start of the file
        //read the the width and the height
        fgets(line, sizeof(line), file);
        sscanf(line, "%d %d", &width, &height);

        //store initial box values
        full_matrix = (float *)malloc(sizeof(float)*width*height);
        memset(full_matrix, 0, sizeof(float)*width*height);

        //read the rest
        int row = 0, col = 0;
        float temp = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            sscanf(line, "%d %d %f", &col, &row, &temp);
            full_matrix[row * width + col] = temp;
        }
        // close the file
        fclose(file);
    }
////////////////////////////////////////////////////////////////////////////////
  
    MPI_Bcast(&height, 1, MPI_INT, scatter_root, MPI_COMM_WORLD);
    MPI_Bcast(&width, 1, MPI_INT, scatter_root, MPI_COMM_WORLD);

    int max_nmb_mpi_proc = nmb_mpi_proc > height ? height : nmb_mpi_proc;

    // With this expression we round the quotient up.
    int loc_lines = (height - 1) / max_nmb_mpi_proc + 1;
  
    int pos, poss[nmb_mpi_proc];
    int len, lens[nmb_mpi_proc];
    memset(poss, 0, sizeof(int)*nmb_mpi_proc);
    memset(lens, 0, sizeof(int)*nmb_mpi_proc);
    if ( mpi_rank == scatter_root )
      for ( int jx = 0, pos = 0; jx < nmb_mpi_proc; ++jx, pos += loc_lines) {
        poss[jx] = pos;
        poss[jx] *= width;
        lens[jx] = pos + loc_lines <= height ? loc_lines : height - pos;
        lens[jx] *= width;
        //fprintf(stderr, "len pos %d %d\n", lens[jx], poss[jx]);
        if (lens[jx] <= 0) {
            poss[jx] = 0;
            lens[jx] = 0;
            break;
        }
      }

    // The sendcount argument determines the number of elements sent to EACH
    // process.
    MPI_Scatter(poss, 1, MPI_INT, &pos, 1, MPI_INT, scatter_root, MPI_COMM_WORLD);
    MPI_Scatter(lens, 1, MPI_INT, &len, 1, MPI_INT, scatter_root, MPI_COMM_WORLD);

    // Allocate local arrays and prepare data on the scatter root.
    float *loc_buff = (float *)malloc(sizeof(float)*len);

    MPI_Scatterv(full_matrix, lens, poss, MPI_FLOAT, loc_buff, len, MPI_FLOAT,
        scatter_root, MPI_COMM_WORLD);

////////////////////////////////////////////////////////////////////////////////
    loc_lines = len/width;
//    fprintf(stderr, "loc_lines %d\n", loc_lines);

    float (*loc_matrix)[width+2] = (float (*)[width+2])malloc((loc_lines+2)*sizeof(float[width+2]));
    float (*loc_matrix_bk)[width+2] = (float (*)[width+2])malloc((loc_lines+2)*sizeof(float[width+2]));
    float (*loc_matrix_temp)[width+2] = NULL;
    memset(loc_matrix, 0, sizeof(float)*(loc_lines+2)*(width+2));
    memset(loc_matrix_bk, 0, sizeof(float)*(loc_lines+2)*(width+2));
    for (size_t ix = 0; ix < loc_lines; ++ix) {
        memcpy(&loc_matrix[ix+1][1], loc_buff+ix*width, sizeof(float)*width);
    }
    
    // iteration
    MPI_Status status;
    for (size_t it = 0; it < iter_num; ++it) {
        // init
        if (max_nmb_mpi_proc > 1) {
            if (mpi_rank == 0) {
                // send last line down
                MPI_Send(&loc_matrix[loc_lines][1], width, MPI_FLOAT, mpi_rank + 1, 0, MPI_COMM_WORLD);
                MPI_Recv(&loc_matrix[loc_lines+1][1], width, MPI_FLOAT, mpi_rank + 1, 0, MPI_COMM_WORLD, &status);
                
            } else if (mpi_rank == max_nmb_mpi_proc-1) {
                MPI_Recv(&loc_matrix[0][1], width, MPI_FLOAT, mpi_rank - 1, 0, MPI_COMM_WORLD, &status);
                // send first line up
                MPI_Send(&loc_matrix[1][1], width, MPI_FLOAT, mpi_rank - 1, 0, MPI_COMM_WORLD);
            } else if (mpi_rank >= max_nmb_mpi_proc) {
                // do nothing
            } else {
                MPI_Recv(&loc_matrix[0][1], width, MPI_FLOAT, mpi_rank - 1, 0, MPI_COMM_WORLD, &status);
                // send last line down
                MPI_Send(&loc_matrix[loc_lines][1], width, MPI_FLOAT, mpi_rank + 1, 0, MPI_COMM_WORLD);
                MPI_Recv(&loc_matrix[loc_lines+1][1], width, MPI_FLOAT, mpi_rank + 1, 0, MPI_COMM_WORLD, &status);
                // send first line up
                MPI_Send(&loc_matrix[1][1], width, MPI_FLOAT, mpi_rank - 1, 0, MPI_COMM_WORLD);
                
            }
        }
        // diffuse
        for (size_t ix = 1; ix < loc_lines+1; ++ix) {
            for (size_t jx = 1; jx < width+1; ++jx) {
                loc_matrix_bk[ix][jx] = loc_matrix[ix][jx] + diff_const * ((loc_matrix[ix-1][jx]+loc_matrix[ix+1][jx]+loc_matrix[ix][jx-1]+loc_matrix[ix][jx+1])/4 - loc_matrix[ix][jx]);
            }
        }

        loc_matrix_temp = loc_matrix_bk;
        loc_matrix_bk = loc_matrix;
        loc_matrix = loc_matrix_temp;
    }

    // TODO: debug
//    for (size_t ix = 1; ix < loc_lines+1; ++ix) {
//        char temp[100];
//        int idx = 0;
//        idx = sprintf(temp+idx, "%d:", mpi_rank);
//        for (size_t jx = 1; jx < width+1; ++jx) {
//            idx += sprintf(temp+idx, "%f ", loc_matrix[ix][jx]);
//        }
//        printf("%s\n", temp);
//    }

    for (size_t ix = 0; ix < loc_lines; ++ix) {
        memcpy(loc_buff+ix*width, &loc_matrix[ix+1][1], sizeof(float)*width);
    }

    free(loc_matrix);
    free(loc_matrix_bk);
////////////////////////////////////////////////////////////////////////////////

    int loc_sum = 0, sum;
    for (size_t ix = 0; ix < len; ++ix) {
        loc_sum += loc_buff[ix];
    }
  
    MPI_Reduce(&loc_sum, &sum, 1, MPI_INT, MPI_SUM, scatter_root, MPI_COMM_WORLD);

    float avg = sum/(width*height);
    if (mpi_rank == scatter_root)
        printf("average of temperatures: %f\n", avg);
  
    MPI_Gatherv(loc_buff, len, MPI_FLOAT, full_matrix, lens, poss, MPI_FLOAT,
        scatter_root, MPI_COMM_WORLD);
  
    if (mpi_rank == scatter_root) {
        int abs_sum = 0;
        for (size_t ix = 0; ix < height; ++ix)
        {
            for (size_t iy = 0; iy < width; iy++)
            {
                abs_sum += fabs(full_matrix[ix * width + iy] - avg);
            }
        }
        printf("absolute difference of each temperature: %f\n", (float)abs_sum/(width*height));
    }

    MPI_Finalize();
    free(loc_buff);
    free(full_matrix);

    return 0;
}
