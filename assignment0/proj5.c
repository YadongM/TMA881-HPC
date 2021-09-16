#include <stdio.h>
#include <stdlib.h>

int
main(
    int argc,
    char *argv[]
    )
{
    int size = 10;

    // Prepare the data

    int ** as = (int**) malloc(sizeof(int*) * size);
    for ( size_t ix = 0; ix < size; ++ix )
        as[ix] = (int*) malloc(sizeof(int) * size);

    for ( size_t ix = 0; ix < size; ++ix )
        for ( size_t jx = 0; jx < size; ++jx )
            as[ix][jx] = 10*ix + jx;

    printf("%d\n", as[0][0]);





    // int * asentries = (int*) malloc(sizeof(int) * size*size);
    // int ** as = (int**) malloc(sizeof(int*) * size);
    // for ( size_t ix = 0, jx = 0; ix < size; ++ix, jx+=size )
    //     as[ix] = asentries + jx;

    // for ( size_t ix = 0; ix < size; ++ix )
    //     for ( size_t jx = 0; jx < size; ++jx ){
    //         as[ix][jx] = 10*ix + jx;
    //         printf("%i\n",as[ix][jx]);
    //     }




    // open the file and write
    FILE *file =  fopen("test_file", "w");


    fwrite((void*) *as, sizeof(int), 100, file);

    // for (size_t ix = 0; ix < size; ++ix)
    //     fwrite((void*) as[ix], sizeof(int), 10, file);

    // finally, close the file
    fclose(file);

    printf("**********************\n");
    printf("Finish Writing \n");
    printf("**********************\n");


    int file_re[size][size];
    file =  fopen("test_file", "r");
    fread((void*) file_re, sizeof(int), 100, file);
    fclose(file);

    for ( size_t ix = 0; ix < size; ++ix )
        for ( size_t jx = 0; jx < size; ++jx ){
            printf("%i", file_re[ix][jx]);
            printf("\n");
        }


    // int * bsentries = (int*) malloc(sizeof(int) * size*size);
    // int ** bs = (int**) malloc(sizeof(int*) * size);
    // for ( size_t ix = 0, jx = 0; ix < size; ++ix, jx+=size )
    //     bs[ix] = bsentries + jx;
    // file =  fopen("test_file", "r");

    // for (size_t ix = 0; ix < size; ++ix)
    //     fread((void*) bs[ix], sizeof(int), 10, file);
    // fclose(file);

    // for ( int ix = 0; ix < size; ++ix )
    //     for ( size_t jx = 0; jx < size; ++jx )
    //         printf("%i\n", bs[ix][jx]);




}

