#include<stdio.h>
main()
{
    int size = 10;

    int * asentries = (int*) malloc(sizeof(int) * size*size);
    int ** as = (int**) malloc(sizeof(int*) * size);
    for ( size_t ix = 0, jx = 0; ix < size; ++ix, jx+=size )
        as[ix] = asentries + jx;

    for ( size_t ix = 0; ix < size; ++ix )
        for ( size_t jx = 0; jx < size; ++jx )
            as[ix][jx] = 10*ix + jx;
    FILE *file =  fopen("test_file", "w");

    for (size_t ix = 0; ix < size; ++ix)
        fwrite((void*) as[ix], sizeof(int), 10, file);
    fclose(file);
    free(as);
    free(asentries);
    // system("pause");




    int * bsentries = (int*) malloc(sizeof(int) * size*size);
    int ** bs = (int**) malloc(sizeof(int*) * size);
    for ( size_t ix = 0, jx = 0; ix < size; ++ix, jx+=size )
        bs[ix] = bsentries + jx;
    file =  fopen("test_file", "r");
    // As with writing we pass the size of one array element and the number of
    // elements that we want to write.
    for (size_t ix = 0; ix < size; ++ix)
        fread((void*) bs[ix], sizeof(int), 10, file);
    fclose(file);

    printf("read after first write: ");
    for ( int ix = 0; ix < size; ++ix )
        for ( size_t jx = 0; jx < size; ++jx )
            printf("%i ", bs[ix][jx]);
}