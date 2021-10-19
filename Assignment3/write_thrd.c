#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdatomic.h>
#include "common.h"
#include "write_thrd.h"

// Define color for drawing attractor image
char *colormap[10] = {
    "158 001 066 ", "216 062 079 ", "244 109 067 ", "253 174 097 ", "254 224 139 ",
    "230 245 152 ", "171 221 164 ", "102 194 165 ", "050 136 189 ", "094 079 162 "
};


char *colormap_gray[105] = {
    "005 005 005 ", "007 007 007 ", "009 009 009 ", "011 011 011 ", "013 013 013 ",
    "017 017 017 ", "019 019 019 ", "021 021 021 ", "023 023 023 ", "025 025 025 ",
    "029 029 029 ", "031 031 031 ", "033 033 033 ", "035 035 035 ", "037 037 037 ",
    "041 041 041 ", "043 043 043 ", "045 045 045 ", "047 047 047 ", "049 049 049 ",
    "053 053 053 ", "055 055 055 ", "057 057 057 ", "059 059 059 ", "061 061 061 ",
    "065 065 065 ", "067 067 067 ", "069 069 069 ", "071 071 071 ", "073 073 073 ",
    "077 077 077 ", "079 079 079 ", "081 081 081 ", "083 083 083 ", "085 085 085 ",
    "089 089 089 ", "091 091 091 ", "093 093 093 ", "095 095 095 ", "097 097 097 ",
    "101 101 101 ", "103 103 103 ", "105 105 105 ", "107 107 107 ", "109 109 109 ",
    "113 113 113 ", "115 115 115 ", "117 117 117 ", "119 119 119 ", "121 121 121 ",
    "125 125 125 ", "127 127 127 ", "129 129 129 ", "131 131 131 ", "133 133 133 ",
    "137 137 137 ", "139 139 139 ", "141 141 141 ", "143 143 143 ", "145 145 145 ",
    "149 149 149 ", "151 151 151 ", "153 153 153 ", "155 155 155 ", "157 157 157 ",
    "161 161 161 ", "163 163 163 ", "165 165 165 ", "167 167 167 ", "169 169 169 ",
    "173 173 173 ", "175 175 175 ", "177 177 177 ", "179 179 179 ", "181 181 181 ",
    "185 185 185 ", "187 187 187 ", "189 189 189 ", "191 191 191 ", "193 193 193 ",
    "197 197 197 ", "199 199 199 ", "201 201 201 ", "203 203 203 ", "205 205 205 ",
    "209 209 209 ", "211 211 211 ", "213 213 213 ", "215 215 215 ", "217 217 217 ",
    "221 221 221 ", "223 223 223 ", "225 225 225 ", "227 227 227 ", "229 229 229 ",
    "233 233 233 ", "235 235 235 ", "237 237 237 ", "239 239 239 ", "241 241 241 ",
    "245 245 245 ", "247 247 247 ", "249 249 249 ", "251 251 251 ", "253 253 253 "
};

int write_thrd_func(void *args)
{
    write_thrd_info_t *write_thrd_info = (write_thrd_info_t*) args;
    TYPE_ROW *result = write_thrd_info->shared_result;
    cnd_t *cnd = write_thrd_info->cnd;
    FILE *atr_file = write_thrd_info->atr_file;
    FILE *conv_file = write_thrd_info->conv_file;

    char attractor_str[nsize * 12];
    char convergence_str[nsize * 12];

    TYPE_ATTR *attr_row; // read a row of attractor result
    TYPE_CONV *conv_row; // read a row of convergence result

    for (int ix = 0; ix < nsize; ++ix) {
        mtx_lock(write_thrd_info->mtx);
        while (!result[ix].done) {
            cnd_wait(cnd, write_thrd_info->mtx);
        }
        mtx_unlock(write_thrd_info->mtx);

        attr_row = result[ix].attractor;
        conv_row = result[ix].convergence;
        for (int jx = 0; jx < nsize; ++jx) {
            memcpy(attractor_str + 12 * jx, colormap[attr_row[jx]], 12*sizeof(char));
            memcpy(convergence_str + 12 * jx, colormap_gray[conv_row[jx]], 12*sizeof(char));
        }
        
        attractor_str[12 * nsize - 1] = '\n';
        convergence_str[12 * nsize - 1] = '\n';

        free(result[ix].attractor);
        free(result[ix].convergence);

        // save into ppm files
        fwrite(attractor_str, sizeof(char), 12 * nsize, atr_file);
        fwrite(convergence_str, sizeof(char), 12 * nsize, conv_file);
    }

    return 0;
}