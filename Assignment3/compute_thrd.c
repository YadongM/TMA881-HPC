#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include <threads.h>
#include "common.h"
#include "compute_thrd.h"

int get_next_row_idx()
{
    static atomic_int i = 0;

    return atomic_fetch_add_explicit(&i, 1, memory_order_relaxed);
}

void iter_result(double *re_re, double *re_im, double a_re, double a_im, int degree)
{
    double temp_re = a_re, temp_im = a_im, temp;
    for(int ix = 2; ix <= degree; ix++)
    {
        temp = temp_re * a_re - temp_im * a_im;
        temp_im = temp_re * a_im + temp_im * a_re;
        temp_re = temp;
    }
    *re_re = temp_re;
    *re_im = temp_im;
}

void computer_newton1(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[1] = {1}, attractor_im[1] = {0};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 0; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        real = 1;
        imaginary = 0;
    }
    *convergence = conv;
}

void computer_newton2(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[2] = {1, -1}, attractor_im[2] = {0, 0};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 1; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        double norm = real * real + imaginary * imaginary;
        prime_re = real / norm;
        prime_im = 0 - imaginary / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 2;
        imaginary -= temp_im / 2;
    }
    *convergence = conv;
}

void computer_newton3(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[3] = {1, -0.5, -0.5}, attractor_im[3] = {0, 0.86603, -0.86603};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 2; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 2);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 3;
        imaginary -= temp_im / 3;

    }
    *convergence = conv;
}

void computer_newton4(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[4] = {1, 0, -1, 0}, attractor_im[4] = {0, 1, 0, -1};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 3; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 3);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 4;
        imaginary -= temp_im / 4;

    }
    *convergence = conv;
}

void computer_newton5(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[5] = {1, 0.309017, -0.809017, -0.809017, 0.309017}, attractor_im[5] = {0, 0.951057, 0.587785, -0.587785, -0.951057};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 4; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 4);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 5;
        imaginary -= temp_im / 5;

    }
    *convergence = conv;
}

void computer_newton6(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[6] = {1, 0.5, -0.5, -1, -0.5, 0.5}, attractor_im[6] = {0, 0.866025, 0.866025, 0, -0.866025, -0.866025};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 5; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 5);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 6;
        imaginary -= temp_im / 6;

    }
    *convergence = conv;
}

void computer_newton7(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[7] = {1, 0.62349, -0.222521, -0.900969, -0.900969, -0.222521, 0.62349},
            attractor_im[7] = {0, 0.781831, 0.974928, 0.433884, -0.433884, -0.974928, -0.781831};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 6; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 6);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 7;
        imaginary -= temp_im / 7;

    }
    *convergence = conv;
}

void computer_newton8(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[8] = {1, 0.707107, 0, -0.707107, -1, -0.707107, 0, 0.707107},
            attractor_im[8] = {0, 0.707107, 1, 0.707107, 0, -0.707107, -1, -0.707107};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 7; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 7);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 8;
        imaginary -= temp_im / 8;

    }
    *convergence = conv;
}

void computer_newton9(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[9] = {1, 0.766044, 0.173648, -0.5, -0.939693, -0.939693, -0.5, 0.173648, 0.766044},
            attractor_im[9] = {0, 0.642788, 0.984808, 0.866025, 0.34202, -0.34202, -0.866025, -0.984808, -0.642788};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = ATTR_DEFAULT_VALUE; ; ++conv)
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = ATTR_DEFAULT_VALUE;
            break;
        }
        for (int ix = 0; ix <= 8; ++ix)
        {
            double delta_re = real - attractor_re[ix];
            double delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        }
        if ( attr != ATTR_DEFAULT_VALUE )
            break;
        iter_result(&prime_re, &prime_im, real, imaginary, 8);
        double norm = prime_re * prime_re + prime_im * prime_im;
        prime_re = prime_re / norm;
        prime_im = 0 - prime_im / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 9;
        imaginary -= temp_im / 9;

    }
    *convergence = conv;
}

void computer_newton(double x_re, double x_im, TYPE_ATTR* attractor, TYPE_CONV* convergence)
{
    *attractor = ATTR_DEFAULT_VALUE;
    *convergence = 0;

    switch(exponent) {
    case 1:
        computer_newton1(x_re, x_im, attractor, convergence);
        break;
    case 2:
        computer_newton2(x_re, x_im, attractor, convergence);
        break;
    case 3:
        computer_newton3(x_re, x_im, attractor, convergence);
        break;
    case 4:
        computer_newton4(x_re, x_im, attractor, convergence);
        break;
    case 5:
        computer_newton5(x_re, x_im, attractor, convergence);
        break;
    case 6:
        computer_newton6(x_re, x_im, attractor, convergence);
        break;
    case 7:
        computer_newton7(x_re, x_im, attractor, convergence);
        break;
    case 8:
        computer_newton8(x_re, x_im, attractor, convergence);
        break;
    case 9:
        computer_newton9(x_re, x_im, attractor, convergence);
        break;

    }
}

int compute_thrd_func(void *args)
{
    const thrd_info_t *thrd_info = (thrd_info_t*) args;
    cnd_t *cnd = thrd_info->cnd;

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

        thrd_sleep(&(struct timespec){.tv_sec=0, .tv_nsec=1000}, NULL);
        atomic_store(&row->done, true); // use memory_order_seq_cst by default
        cnd_signal(cnd);
    }
    return 0;
}
