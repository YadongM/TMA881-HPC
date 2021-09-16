#include <stdio.h>
#include<time.h>


int
main(
    int argc,
    char *argv[]
    )
{

    int a;
    long long sum = 0;

    clock_t start, stop;
    start = clock();

    for (a = 0; a <= 1000000000; ++a)
        sum += a;
    printf("Sum = %lld\n", sum);

    stop = clock();
    double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
 
    printf("Time cost = %lf s\n", duration);
    return 0;
}

