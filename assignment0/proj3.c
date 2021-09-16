#include <stdio.h>
#include <stdlib.h>

int main(
    int argc,
    char *argv[]
)

{
    int size = 10;

    // Not avoiding memory fragmentation
    int ** as = (int**) malloc(sizeof(int*) * size);
    for ( size_t ix = 0; ix < size; ++ix )
        as[ix] = (int*) malloc(sizeof(int) * size);

    for ( size_t ix = 0; ix < size; ++ix )
        for ( size_t jx = 0; jx < size; ++jx )
            as[ix][jx] = 0;

    printf("%d\n", as[0][0]);

    for ( size_t ix = 0; ix < size; ++ix )
        free(as[ix]);
    free(as);
}
