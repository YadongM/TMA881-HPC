#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include "common.h"
#include "compute_thrd.h"
#include "write_thrd.h"

const int ATTR_DEFAULT_VALUE = 0;

int nsize = 10;
int nthrds = 18;
int exponent = 3;

int main()
{
    // TODO:
    // Parsing command line arguments and store into 
    //int nsize
    //int nthrds
    //int exponent

    TYPE_ROW *result = (TYPE_ROW *)malloc(nsize * sizeof(TYPE_ROW));
    for (int ix = 0; ix < nsize; ++ix) {
        result[ix].done = false;
    }
    
    // start computing threads
    thrd_t compute_thrds[nthrds];
    thrd_info_t compute_thrds_info[nthrds];
    for (int tx = 0; tx < nthrds; ++tx) {
        compute_thrds_info[tx].shared_result = result;
        int r = thrd_create(compute_thrds+tx, compute_thrd_func, (void*) (compute_thrds_info+tx));
        if (r != thrd_success) {
            fprintf(stderr, "failed to create computing thread %d\n", tx);
            exit(1);
        }
    }

    // start writing thread
    thrd_t write_thrd;
    thrd_info_t write_thrds_info;
    write_thrds_info.shared_result = result;
    int r = thrd_create(&write_thrd, write_thrd_func, (void *)&write_thrds_info);
    if (r != thrd_success) {
        fprintf(stderr, "failed to create writing thread\n");
        exit(1);
    }

    // wait for all the threads
    for (int tx = 0; tx < nthrds; ++tx) {
        int r;
        thrd_join(compute_thrds[tx], &r);
    }
    thrd_join(write_thrd, NULL);

    free(result);
    
    return 0;
}
