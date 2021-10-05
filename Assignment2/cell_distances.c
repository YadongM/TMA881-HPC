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
#define BATCH_SIZE 5

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
    size_t batch_size = (batch_num==1) ? line_num : BATCH_SIZE;
    printf("Batch size = %d\nBatch num = %d\n", batch_size, batch_num);

    // allocate memory for storing read lines
    
    int (*batch_1)[3] = (int (*)[3])malloc(batch_size * sizeof(int[3]));
    int (*batch_2)[3] = (int (*)[3])malloc(batch_size * sizeof(int[3]));
    fseek(file, 0, SEEK_SET); // to the start of the file
    
    char per_line[25]; // for storing a line's info
    char temp_str[7]; // for string to integer
    // Outer loop
    for (size_t batch_out = 0; batch_out < batch_num; batch_out++){
        printf("Outer loop: %d\n", batch_out); // FOR TESTING (delete later)

        file_cursor = batch_out * batch_size * 24;
        fseek(file, file_cursor, SEEK_SET);

        // prepare batch_1 for outer loop
        for (size_t line = 0; line < batch_size; line++){
            fgets(per_line, 25, file);
            for (size_t ix = 0; ix < 3; ++ix) {
                memcpy(temp_str, &per_line[ix * 8], 3);
                memcpy(temp_str+3, &per_line[ix * 8 + 4], 3);
                temp_str[6] = '\0';
                batch_1[line][ix] = (short)atoi(temp_str);
            }
        } // end of prepare batch_1

        // FOR TESTING (delete later) print batch_1 
        for (size_t line = 0; line < batch_size; line++){
            for (size_t ix = 0; ix < 3; ++ix) {
                printf("%d\t", batch_1[line][ix]);
            }
            printf("\n");
        }
        
        fseek(file, file_cursor, SEEK_SET);
        
        // Inner loop
        for (size_t batch_in = batch_out; batch_in < batch_num; batch_in++){
            printf("\tInner loop: %d\n", batch_in); // FOR TESTING (delete later)
            // prepare batch_2 for inner loop
            for (size_t line = 0; line < batch_size; line++){
                fgets(per_line, 25, file);
                for (size_t ix = 0; ix < 3; ++ix) {
                    memcpy(temp_str, &per_line[ix * 8], 3);
                    memcpy(temp_str+3, &per_line[ix * 8 + 4], 3);
                    temp_str[6] = '\0';
                    batch_2[line][ix] = (short)atoi(temp_str);
                }
            } // end of prepare batch_2

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