#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include "common.h"
#include "write_thrd.h"

int colormap[10][3] = {
    {158,1,66}, {216,62,79}, {244,109,67}, {253,174,97}, {254,224,139},
    {230,245,152}, {171,221,164}, {102,194,165}, {50,136,189}, {94,79,162}
};
char charColor[121];
char charGreyColor[400];

int write_thrd_func(void *args)
{
    const write_thrd_info_t *write_thrd_info = (write_thrd_info_t*) args;
    TYPE_ROW *result = write_thrd_info->shared_result;
    cnd_t *cnd = write_thrd_info->cnd;
    FILE *atr_file = write_thrd_info->atr_file;
    FILE *conv_file = write_thrd_info->conv_file;

    mtx_t mtx;
    mtx_init(&mtx, mtx_plain);

    char attractor_str[nsize * 12]; // TODO:change size later
    char convergence_str[nsize * 12];

    TYPE_ATTR *attr_row; // read a row of attractor result
    TYPE_CONV *conv_row; // read a row of convergence result

    int *attr_color;
    int conv_color;

    for (int ix = 0; ix < nsize; ++ix) {
        while (!atomic_load(&result[ix].done)) {
            cnd_wait(cnd, &mtx);
        }

        attr_row = result[ix].attractor;
        conv_row = result[ix].convergence;
        for (int jx = 0; jx < nsize; ++jx) {
            attr_color = colormap[attr_row[jx]];
            sprintf(attractor_str+12*jx, "%03d ", attr_color[0]);
            sprintf(attractor_str+12*jx+4, "%03d ", attr_color[1]);
            sprintf(attractor_str+12*jx+8, "%03d ", attr_color[2]);
            
            conv_color = 255 * (conv_row[jx] + 1) / 100;
            for (int oc = 0; oc < 3; oc++)
                sprintf(convergence_str + 12 * jx + 4 * oc, "%03d ", conv_color);
        }
        
        attractor_str[12 * nsize - 1] = '\n';
        convergence_str[12 * nsize - 1] = '\n';

        free(result[ix].attractor);
        free(result[ix].convergence);

        // save into ppm files
        fwrite(attractor_str, sizeof(char), 12 * nsize, atr_file);
        fwrite(convergence_str, sizeof(char), 12 * nsize, conv_file);
    }

    mtx_destroy(&mtx);
    // return 0;
}
