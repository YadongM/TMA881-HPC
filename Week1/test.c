#include <stdio.h>
#include <stdlib.h>


int main(
    int argc,
    char *argv[]
)

{
    int *asentries = (int*) malloc(3*4*sizeof(int));

    for ( int ix = 0; ix < 3; ++ix ){
        printf("%i\n", asentries);
        printf("%i\n", asentries+1);
    }
    

    //   int *a = asentries + 4*ix;
    //   printf("%i", as[ix]);

}