#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int iter_num = 0;      // iteration number
    float diff_const = 0.; // diffusion constant
    // parsing arguments
    if (argc != 3)
    {
        fprintf(stderr, "Error: Wrong Syntax. Should be in form:\n./diffusion -n[number_of_iterations] -d[diffusion_constant]\n");
        exit(0);
    }
    char *ptr_n, *ptr_d;
    for (size_t ix = 1; ix < argc; ix++)
    {
        ptr_n = strchr(argv[ix], 'n');
        ptr_d = strchr(argv[ix], 'd');
        if (ptr_n)
            iter_num = strtol(++ptr_n, NULL, 10);
        else if (ptr_d)
            diff_const = strtof(++ptr_d, NULL);
    }
    // TEST ONLY
    printf("Iteration Number: %d\n", iter_num);
    printf("Diffusion Constant: %f\n", diff_const);

    // Read the input file
    int width = 0, height = 0; // the width and the height
    char line[100];
    char filename[] = "input";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(0);
    }

    fseek(file, 0, SEEK_SET); // to the start of the file
    int row = 0, col = 0;
    float temp = 0.;
    //read the the width and the height
    fgets(line, sizeof(line), file);
    sscanf(line, "%d %d", &width, &height);
    int sz = width * height;
    printf("Width: %d, Height: %d, Size: %d\n", width, height, sz);

    //store initial box values
    float *init_box = malloc(sz * sizeof(float));
    for (size_t ix = 0; ix < width; ++ix)
    {
        for (size_t iy = 0; iy < height; ++iy)
        {
            init_box[ix * width + iy] = 0;
        }
    }
    //read the rest
    while (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%d %d %f", &row, &col, &temp);
        init_box[row * width + col] = temp;
    }
    // close the file
    fclose(file);

    // TEST ONLY
    printf("\n\nInitial Box: \n");
    for (size_t ix = 0; ix < width; ++ix)
    {
        for (size_t iy = 0; iy < height; iy++)
        {
            printf("%f ", init_box[ix * width + iy]);
        }
        printf("\n");
    }
    return 0;
}