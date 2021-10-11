#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A GLOBAL VAR FOR USER DEFINE BATCH_SIZE
/* We are allowed to use 5 MiB = 5 * 1024^2 bytes of memory.
Through our implementation, Type SHORT is used to store our data and there are two blocks stored in the memory to calculate distances at the same time.
As a result, we calculate the size of each block in the following way, 
BATCH_SIZE = 5 * 1024^2 / (2 * 3 * 2)
, where the first 2 is the size of SHORT, 3 means every point is three dimentional and the second 2 is the num of blocks.
The result is around 436906.
For simplicity and space for other variables, which is relatively small compared with the data, we take it as 400000.
*/

// A GLOBAL VAR FOR USER DEFINE BATCH_SIZE
#define BATCH_SIZE 400000

// Load a batch into defined arrays
void load_batch(int16_t (*batch)[3], size_t size, char * batch_buffer)
{
    size_t line, ix;
    int16_t a0, a1, a2, a4, a5, a6;

    #pragma omp parallel for \
        default(none) private(ix, a0, a1, a2, a4, a5, a6) \
        shared(size, line, batch, batch_buffer)
    
    for (line = 0; line < size; line++) {
        for (ix = 0; ix < 3; ++ix) {
            a0 = 44 - (int16_t)(batch_buffer[line * 24 + 8 * ix + 0]);
            a1 = (int16_t)(batch_buffer[line * 24 + 8 * ix + 1]) - 48;
            a2 = (int16_t)(batch_buffer[line * 24 + 8 * ix + 2]) - 48;
            a4 = (int16_t)(batch_buffer[line * 24 + 8 * ix + 4]) - 48;
            a5 = (int16_t)(batch_buffer[line * 24 + 8 * ix + 5]) - 48;
            a6 = (int16_t)(batch_buffer[line * 24 + 8 * ix + 6]) - 48;
            batch[line][ix] = a0  * (a1 * 10000 + a2 * 1000 + a4 * 100 + a5 * 10 + a6);
        }
    }
}

int16_t calculate_distance(int16_t *cell_1, int16_t *cell_2)
{
    float temp = sqrt((cell_1[0] - cell_2[0]) * (cell_1[0] - cell_2[0])
        + (cell_1[1] - cell_2[1]) * (cell_1[1] - cell_2[1])
        + (cell_1[2] - cell_2[2]) * (cell_1[2] - cell_2[2]));
    return (int16_t)(temp / 10);
}

void distance_of_1batch(int16_t (*batch)[3], size_t len, size_t *count)
{
    size_t ix, jx;
    int16_t distance;

    #pragma omp parallel for \
        default(none) private(ix, jx, distance) \
        shared(batch, len) reduction(+:count[:3465])

    for (ix = 0; ix < len - 1; ix++) {
        for (jx = ix + 1; jx < len; jx++) {
            distance = calculate_distance(batch[ix], batch[jx]);
            count[distance] += 1;
        }
    }
}

void distance_of_2batch(int16_t (*batch_1)[3], int16_t (*batch_2)[3], size_t len_1, size_t len_2, size_t *count)
{
    size_t ix, jx;
    int16_t distance;
    
    #pragma omp parallel for \
        default(none) private(ix, jx, distance) \
        shared(batch_1, batch_2, len_1, len_2) reduction(+:count[:3465])
        
    for (ix = 0; ix < len_1; ix++) {
        for (jx = 0; jx < len_2; jx++) {
            distance = calculate_distance(batch_1[ix], batch_2[jx]);
            count[distance] += 1;
        }
    }
}

int main(int argc, char* argv[])
{
    int n_threads = 20;

    // read command line arguments
    char* ptr = strchr(argv[1], 't');
    if (ptr) {
        n_threads = strtol(++ptr, NULL, 10);
    }
    // Set OpenMP Threads
    omp_set_num_threads(n_threads);
    // printf("OpenMP threads that will be used (n_threads) = %d \n", n_threads);

    // counter vector for tracking counted numbers
    size_t counter[3465] = {0};

    // open the file
    char filename[] = "cells";
    FILE* file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("error opening file\n");
        return -1;
    }
    
    // Check file size and number of lines
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    size_t line_num = (file_size+1)/24;

    long file_cursor = ftell(file); // for store the current file position
    size_t batch_num;
    size_t last_batch_size = line_num % BATCH_SIZE;
    batch_num = (last_batch_size == 0) ? line_num/BATCH_SIZE : line_num/BATCH_SIZE + 1;
    size_t batch_size = (batch_num == 1) ? line_num : BATCH_SIZE;
    size_t outer_batch_size, inner_batch_size; // a dynamic batchsize, should be different when encouter the last batch
    
    char * batch_buffer = (char*)malloc(sizeof(char)*batch_size*24);; // a buffer for loading a batch from text file
    
    // allocate memory for storing read lines
    int16_t (*batch_1)[3] = (int16_t (*)[3])malloc(batch_size * sizeof(int16_t[3]));
    int16_t (*batch_2)[3] = (int16_t (*)[3])malloc(batch_size * sizeof(int16_t[3]));
    
    fseek(file, 0, SEEK_SET); // to the start of the file
    
    // Outer loop
    for (size_t batch_out = 0; batch_out < batch_num; batch_out++) {
        // check if it is the last batch
        outer_batch_size = batch_size;
        if (batch_out == (batch_num - 1)) {
            outer_batch_size = last_batch_size;
        }

        file_cursor = batch_out * batch_size * 24;
        fseek(file, file_cursor, SEEK_SET);

        // prepare batch_1 for outer loop
        fread(batch_buffer, 1, outer_batch_size*24, file);
        load_batch(batch_1, outer_batch_size, batch_buffer);
        
        // calculate distances between batch_1 and batch_1
        distance_of_1batch(batch_1, outer_batch_size, counter);

        file_cursor = (batch_out+1) * batch_size * 24;
        fseek(file, file_cursor, SEEK_SET);
        
        // Inner loop
        for (size_t batch_in = batch_out + 1; batch_in < batch_num; batch_in++) {
            // check if it is the last batch
            inner_batch_size = batch_size;
            if (batch_in == (batch_num - 1)) {
                inner_batch_size = last_batch_size;
            }
            // prepare batch_1 for inner loop
            fread(batch_buffer, 1, inner_batch_size*24, file);
            load_batch(batch_2, inner_batch_size, batch_buffer);

            // calculate distances between batch_1 and batch_2
            distance_of_2batch(batch_1, batch_2, outer_batch_size, inner_batch_size, counter);
        } // end of inner loop
    } // end of outerloop
    
    // print out the results
    for (size_t ix = 0; ix < 3465; ++ix) {
        if (counter[ix] != 0) {
            printf("%05.2f %d\n", ix/100.0, counter[ix]);
        }
    }

    // close the file
    fclose(file);
    // free memory
    free(batch_buffer);
    free(batch_1);
    free(batch_2);

    return 0;
}