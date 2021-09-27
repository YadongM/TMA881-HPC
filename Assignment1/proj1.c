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

    for (a = 0; a <= 1000000000; ++a)
        sum += a;
    printf("%lld", sum);

    return 0;
}
