#include<math.h>

void iter_result(double *re_re, double *re_im, double a_re, double a_im, int degree)
{
    double temp_re = a_re, temp_im = a_im, temp;
    for(int ix = 0; ix < degree / 2; ix++)
    {
        temp = temp_re * temp_re - temp_im * temp_im;
        temp_im = 2 * temp_re * temp_im;
        temp_re = temp;
    }
    if(degree % 2)
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
    for (conv = 0, attr = -1; ; ++conv) 
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = -1;
            break;
        }
        for (int ix = 0; ;++ix)
        {
            int delta_re = real - attractor_re[ix];
            int delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        if ( attr != -1 )
            break;
        real = 1;
        imaginary = 0;
        }
    }
    *convergence = conv;
}

void computer_newton2(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[1] = {1}, attractor_im[1] = {0};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = -1; ; ++conv) 
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = -1;
            break;
        }
        for (int ix = 0; ;++ix)
        {
            int delta_re = real - attractor_re[ix];
            int delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        if ( attr != -1 )
            break;
        double norm = real * real + imaginary * imaginary;
        prime_re = real / norm;
        prime_im = 0 - imaginary / norm;
        temp_re = real - prime_re;
        temp_im = imaginary - prime_im;
        real -= temp_re / 2;
        imaginary -= temp_im / 2;
        }
    }
    *convergence = conv;
}

void computer_newton3(double real, double imaginary, int *attractor, int *convergence)
{
    double attractor_re[1] = {1}, attractor_im[1] = {0};
    int conv, attr;
    double temp_re, temp_im, prime_re, prime_im;
    for (conv = 0, attr = -1; ; ++conv) 
    {
        if ((real * real + imaginary * imaginary) < 0.000001 || real > 10000000000 || real < -10000000000 || imaginary > 10000000000 || imaginary < -10000000000)
        {
            *attractor = -1;
            break;
        }
        for (int ix = 0; ;++ix)
        {
            int delta_re = real - attractor_re[ix];
            int delta_im = imaginary - attractor_im[ix];
            if ((delta_re * delta_re + delta_im * delta_im) < 0.000001)
            {
                attr = ix + 1;
                *attractor = ix + 1;
                break;
            }
        if ( attr != -1 )
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
    }
    *convergence = conv;
}