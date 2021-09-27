#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    const long int bench_iter = 5000;
    struct timespec bench_start_time, bench_stop_time;
    double bench_diff_time;

    srand(time(NULL));

    const int size = 1000;
    double matrix[size][size];
    double sums[size];
    for (int ix = 0; ix < size; ++ix) {
        for (int jx = 0; jx < size; ++jx) {
            // generate a number in form of xx.xx
            matrix[ix][jx] = rand() % 10000 / 100.0;
        }
    }

    timespec_get(&bench_start_time, TIME_UTC);
    for (int bx = 0; bx < bench_iter; ++bx) {
        for ( size_t ix = 0; ix < size; ++ix ) {
            double sum = 0.;
            for ( size_t jx = 0; jx < size; ++jx )
                sum += matrix[ix][jx];
            sums[ix] = sum;
        }
    }
    timespec_get(&bench_stop_time, TIME_UTC);

    {
        int ix = rand() % size;
        volatile double tmp = sums[ix];
    }

    bench_diff_time =
        difftime(bench_stop_time.tv_sec, bench_start_time.tv_sec) * 1000000
        + (bench_stop_time.tv_nsec - bench_start_time.tv_nsec) / 1000;
    printf("benchmark time for one iteration: %fmus\n",
        bench_diff_time / bench_iter);
}