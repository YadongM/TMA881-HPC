#include <stdio.h>
#include <stdlib.h>

int main(
    int argc,
    char *argv[]
)

{
    int size = 8*1024*1024*8;

    int as[size];
    for ( size_t ix = 0; ix < size; ++ix )
        as[ix] = 0;

    printf("%d\n", as[0]);
}
