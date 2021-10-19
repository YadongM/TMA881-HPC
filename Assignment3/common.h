#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdbool.h>
#include <threads.h>

typedef int TYPE_ATTR;
typedef int TYPE_CONV;

extern const int ATTR_DEFAULT_VALUE;

extern int nsize;
extern int nthrds;
extern int exponent;

typedef struct {
    TYPE_ATTR *attractor;
    TYPE_CONV *convergence;
    bool done;
} TYPE_ROW;

typedef struct {
    TYPE_ROW *shared_result;
    cnd_t *cnd;
} thrd_info_t;

typedef struct {
    TYPE_ROW *shared_result;
    cnd_t *cnd;

    // for writing files
    FILE *atr_file;
    FILE *conv_file;
} write_thrd_info_t;

#endif
