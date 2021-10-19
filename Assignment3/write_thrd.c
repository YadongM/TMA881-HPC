#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    write_thrd_info_t *write_thrd_info = (write_thrd_info_t*) args;
    TYPE_ROW *result = write_thrd_info->shared_result;
    cnd_t *cnd = write_thrd_info->cnd;
    FILE *atr_file = write_thrd_info->atr_file;
    FILE *conv_file = write_thrd_info->conv_file;

    char color_str[10][12];
    for (int ix = 0; ix < 10; ++ix) {
        sprintf(color_str[ix], "%03d %03d %03d ", colormap[ix][0], colormap[ix][1], colormap[ix][2]);
    }
    char grey_str[100][12];
    for (int ix = 0; ix < 100; ++ix) {
        sprintf(grey_str[ix], "%03d %03d %03d ", ix, ix, ix);
    }

    char attractor_str[nsize * 12];
    char convergence_str[nsize * 12];

    TYPE_ATTR *attr_row; // read a row of attractor result
    TYPE_CONV *conv_row; // read a row of convergence result

    int *attr_color;
    int conv_color;
    int oc;

    for (int ix = 0; ix < nsize; ++ix) {
        mtx_lock(write_thrd_info->mtx);
        while (!result[ix].done) {
            cnd_wait(cnd, write_thrd_info->mtx);
        }
        mtx_unlock(write_thrd_info->mtx);

        attr_row = result[ix].attractor;
        conv_row = result[ix].convergence;
        for (int jx = 0; jx < nsize; ++jx) {
            memcpy(attractor_str + 12 * jx, color_str[attr_row[jx]], 12*sizeof(char));
            
           // printf("%d ", conv_row[jx] + 1);
            memcpy(convergence_str + 12 * jx, grey_str[conv_row[jx] + 1], 12*sizeof(char));
        }
        
        attractor_str[12 * nsize - 1] = '\n';
        convergence_str[12 * nsize - 1] = '\n';

        free(result[ix].attractor);
        free(result[ix].convergence);

        // save into ppm files
        fwrite(attractor_str, sizeof(char), 12 * nsize, atr_file);
        fwrite(convergence_str, sizeof(char), 12 * nsize, conv_file);
    }

    // return 0;
}
