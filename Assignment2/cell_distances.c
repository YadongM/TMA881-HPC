#include "omp.h"
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// A GLOBAL VAR FOR USER DEFINE BATCH_SIZE
#define BATCH_SIZE 3

void load_batch(int (*batch)[3], size_t size, FILE* file)
{
    char per_line[25]; // for storing a line's info
    char temp_str[7]; // for string to integer
    for (size_t line = 0; line < size; line++){
        fgets(per_line, 25, file);
        for (size_t ix = 0; ix < 3; ++ix) {
            memcpy(temp_str, &per_line[ix * 8], 3);
            memcpy(temp_str+3, &per_line[ix * 8 + 4], 3);
            temp_str[6] = '\0';
            batch[line][ix] = (short)atoi(temp_str);
        }
    }
}

short calculate_distance(short *Num_1, short *Num_2){
    float temp = sqrt((Num_1[0] - Num_2[0]) * (Num_1[0] - Num_2[0])
        + (Num_1[1] - Num_2[1]) * (Num_1[1] - Num_2[1])
        + (Num_1[2] - Num_2[2]) * (Num_1[2] - Num_2[2]));
    return (short)(temp / 10 + 0.5);
}

void self_distance(int (*Batch)[3], size_t len, size_t *count){
    for ( size_t ix = 0; ix < len - 1; ix++) {
        for ( size_t jx = ix + 1; jx < len; jx++) {
            short distance = calculate_distance(Batch[ix], Batch[jx]);
            count[distance] += 1;
    }
  }
}

void double_distance(int (*Batch_1)[3], int (*Batch_2)[3], size_t len_1, size_t len_2, size_t *count){
    for ( size_t ix = 0; ix < len_1; ix++) {
        for ( size_t jx = 0; jx < len_2; jx++) {
            short distance = calculate_distance(Batch_1[ix], Batch_2[jx]);
            count[distance] += 1;
    }
  }
}

int main(int argc, char* argv[])
{
    // counter vector for tracking counted numbers
    size_t counter[3465] = {0};
    
    // read command line arguments
    int n_threads = 1;
    char* ptr = strchr(argv[1], 't');
    if (ptr) {
        n_threads = strtol(++ptr, NULL, 10);
    }
    printf("OpenMP threads that will be used (n_threads) = %d \n", n_threads);
    
    // 
    // omp_set_num_threads(n_threads);

    // open the file
    char filename[] = "dis_file";
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening file\n");
        return -1;
    }
    
    // Check file size and number of lines
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    size_t line_num = (file_size+1)/24;
    printf("File size = %d\nLine number = %d\n", file_size, line_num);

    long file_cursor = ftell(file); // for store the current file position
    size_t batch_num;
    size_t last_batch_size = line_num % BATCH_SIZE;
    batch_num = (last_batch_size == 0) ? line_num/BATCH_SIZE : line_num/BATCH_SIZE + 1;
    size_t batch_size = BATCH_SIZE;
    printf("Batch size = %d\nBatch num = %d\n", batch_size, batch_num);

    // allocate memory for storing read lines
    
    int (*batch_1)[3] = (int (*)[3])malloc(batch_size * sizeof(int[3]));
    int (*batch_2)[3] = (int (*)[3])malloc(batch_size * sizeof(int[3]));
    fseek(file, 0, SEEK_SET); // to the start of the file
    
    // Outer loop
    for (size_t batch_out = 0; batch_out < batch_num; batch_out++){
        size_t batch_size1;
        // check if it is the last batch
        batch_size1 = batch_size;
        if (batch_out == (batch_num - 1)){
            batch_size1 = last_batch_size;
        }

        printf("Outer loop: %d\n", batch_out); // FOR TESTING (delete later)

        file_cursor = batch_out * batch_size * 24;
        fseek(file, file_cursor, SEEK_SET);

        // prepare batch_1 for outer loop
        load_batch(batch_1, batch_size1, file);

        self_distance(batch_1, batch_size1, counter);

        // FOR TESTING (delete later) print batch_1 
        for (size_t line = 0; line < batch_size; line++){
            for (size_t ix = 0; ix < 3; ++ix) {
                printf("%d\t", batch_1[line][ix]);
            }
            printf("\n");
        }

        file_cursor = (batch_out+1) * batch_size * 24;
        fseek(file, file_cursor, SEEK_SET);
        
        // Inner loop
        for (size_t batch_in = batch_out + 1; batch_in < batch_num; batch_in++){
            size_t batch_size2;
            // check if it is the last batch
            batch_size2 = batch_size;
            if (batch_in == (batch_num - 1)){
                batch_size2 = last_batch_size;
            }
            printf("\tInner loop: %d\n", batch_in); // FOR TESTING (delete later)
            load_batch(batch_2, batch_size2, file);

            double_distance(batch_1, batch_size1, batch_2, batch_size2, counter);

            // FOR TESTING (delete later) print batch_2 
            for (size_t line = 0; line < batch_size; line++){
                for (size_t ix = 0; ix < 3; ++ix) {
                    printf("\t\t%d\t", batch_2[line][ix]);
                }
                printf("\n");
            }

            // TODO: calculate distances

        } // end of inner loop
    } // end of outerloop
    

    // close the file
    fclose(file);
    // free memory
    free(batch_1);
    free(batch_2);

    return 0;
}
