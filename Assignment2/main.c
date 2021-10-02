#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE * pFile;
    pFile = fopen ("cells" , "r+");
    if (pFile == NULL) {
        perror ("Error opening file");
        return 1;
    }

    // TODO: read from file and parse input

    // TODO: computer distance

    //balabalabala

    fclose (pFile);
    return 0;
}
