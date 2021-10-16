#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include <unistd.h>
#include "common.h"
#include "write_thrd.h"

int write_thrd_func(void *args)
{
    const thrd_info_t *thrd_info = (thrd_info_t*) args;
    TYPE_ROW *result = thrd_info->shared_result;

    char attractor_str[nsize*10]; // TODO:change size later
    char convergence_str[nsize*10];
    for (int ix = 0; ix < nsize; ++ix) {
        if (atomic_load(&result[ix].done)) {
            int astr_idx = 0;
            int cstr_idx = 0;
            for (int jx = 0; jx < nsize; ++jx) {
                astr_idx += sprintf(&attractor_str[astr_idx], "%3d ", result[ix].attractor[jx]);
                cstr_idx += sprintf(&convergence_str[cstr_idx], "%3d ", result[ix].convergence[jx]);
            }
            attractor_str[astr_idx] = '\0';
            convergence_str[cstr_idx] = '\0';

            free(result[ix].attractor);
            free(result[ix].convergence);
        } else {
            usleep(10);
            --ix;
        }

        // TODO: save into ppm files
        printf("attractor\t%d: %s\n", ix, attractor_str);
        printf("convergence\t%d: %s\n", ix, convergence_str);
    }
    return 0;
}
