#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <threads.h>
#include "common.h"
#include "compute_thrd.h"
#include "write_thrd.h"

const int ATTR_DEFAULT_VALUE = -1;

int nsize, nthrds, exponent;

int main(int argc, char *argv[])
{
    if (argc != 4){
        fprintf(stderr, "Error: Wrong Syntax. Should be in form:\n./newton -t[number_of_thread] -l[size_of_image] [exponent]\n");
        exit(0);
    }
    char *ptr_t, *ptr_l;
    for (size_t ix = 1; ix < argc; ix++)
    {
        ptr_t = strchr(argv[ix], 't');
        ptr_l = strchr(argv[ix], 'l');
        if (ptr_t) nthrds = strtol(++ptr_t, NULL, 10);
        else if (ptr_l) nsize = strtol(++ptr_l, NULL, 10);
        else exponent = strtol(argv[ix], NULL, 10);
    }

    TYPE_ROW *result = (TYPE_ROW *)malloc(nsize * sizeof(TYPE_ROW));
    for (int ix = 0; ix < nsize; ++ix) {
        result[ix].done = false;
    }

    cnd_t cnd;
    cnd_init(&cnd);
    
    // start computing threads
    thrd_t compute_thrds[nthrds];
    thrd_info_t compute_thrds_info[nthrds];
    for (int tx = 0; tx < nthrds; ++tx) {
        compute_thrds_info[tx].shared_result = result;
        compute_thrds_info[tx].cnd = &cnd;
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
    write_thrds_info.cnd = &cnd;
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
    cnd_destroy(&cnd);
    
    return 0;
}
