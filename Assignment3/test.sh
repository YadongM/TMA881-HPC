make clean
tar czvf submission.tar.gz main.c write_thrd.c write_thrd.h common.h compute_thrd.c compute_thrd.h common.h makefile
/home/hpc2021/newton_iteration/check_submission.py ./submission.tar.gz

