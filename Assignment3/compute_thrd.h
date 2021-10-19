#ifndef _COMPUTE_THRD_H_
#define _COMPUTE_THRD_H_

typedef struct {
    TYPE_ROW *shared_result;
    mtx_t *mtx;
    cnd_t *cnd;
} thrd_info_t;

int compute_thrd_func(void *args);

#endif
