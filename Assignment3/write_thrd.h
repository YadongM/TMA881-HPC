#ifndef _WRITE_THRD_H_
#define _WRITE_THRD_H_

typedef struct {
    TYPE_ROW *shared_result;
    mtx_t *mtx;
    cnd_t *cnd;

    // for writing files
    FILE *atr_file;
    FILE *conv_file;
} write_thrd_info_t;

int write_thrd_func(void *args);

#endif
