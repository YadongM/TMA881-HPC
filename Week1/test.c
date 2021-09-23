#include <stdio.h>
#include <stdlib.h>


int main(
    int argc,
    char *argv[]
)

{
    int a = 1;
    
    int *ap = &a;
    printf("%i\n", (*ap+1));





    // printf("%i\n", &a);
    // printf("%i\n", *(&a));

}