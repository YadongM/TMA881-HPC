#include "omp.h"
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    if ( file == NULL ) {
        printf("error opening file\n");
        return -1;
    }
    
    // Check file size and number of lines
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    size_t line_num = (file_size+1)/24;
    printf("File size = %d\nLine number = %d\n", file_size, line_num);

    // apply memory for storing read lines
    size_t batch_size = 3;
    int (*batch_1)[3] = (int (*)[3])malloc(batch_size * sizeof(int[3]));
    int (*batch_2)[3] = (int (*)[3])malloc(batch_size * sizeof(int[3]));
    fseek(file, 0, SEEK_SET); // to the start of the file
    long file_cursor = ftell(file);

    while (ftell(file) != file_size){
        char per_line[25];
        for (size_t line = 0; line < batch_size; line++){
            fgets(per_line, 25, file);
            for (size_t ix = 0; ix < 3; ++ix) {
                char temp_str[7];
                memcpy(temp_str, &per_line[ix*8], 3);
                memcpy(temp_str+3, &per_line[ix*8+4], 3);
                temp_str[6] = '\0';
                batch_1[line][ix] = (short)atoi(temp_str);
            }
        }

    }
    for (size_t line = 0; line < batch_size; line++){
        for (size_t ix = 0; ix < 3; ++ix) {
            printf("%d\t", batch_1[line][ix]);
        }
        printf("\n");
    }
    // close the file
    fclose(file);
    free(batch_1);
    free(batch_2);

    return 0;
}