#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include "common.h"
#include "compute_thrd.h"

int get_next_row_idx()
{
    static atomic_int i = 0;

    return atomic_fetch_add_explicit(&i, 1, memory_order_relaxed);
}

void computer_newton(double x_re, double x_im, TYPE_ATTR* attractor, TYPE_CONV* convergence)
{
    // TODO
    *attractor = ATTR_DEFAULT_VALUE;
    *convergence = 0;
}

int compute_thrd_func(void *args)
{
    const thrd_info_t *thrd_info = (thrd_info_t*) args;

    while(true) {
        int row_idx = get_next_row_idx();
        if (row_idx >= nsize) {
            break;
        }

        TYPE_ROW *row = thrd_info->shared_result + row_idx;
        row->attractor = (TYPE_ATTR *)malloc(nsize * sizeof(TYPE_ATTR));
        row->convergence = (TYPE_CONV *)malloc(nsize * sizeof(TYPE_CONV));

        double real = -2 + (4.0 / nsize) * 0.5;
        double image = -2 + (4.0 / nsize) * (row_idx + 0.5);
        for (int ix = 0; ix < nsize; ++ix) {
            computer_newton(real, image, &row->attractor[ix], &row->convergence[ix]);
            real += 4.0 / nsize;
        }

        atomic_store(&row->done, true); // use memory_order_seq_cst by default
    }
    return 0;
}
