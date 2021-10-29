CC := gcc
BINS = diffusion
CFLAGS = -O2 -lOpenCL

.PHONY : all
all : $(BINS) 

diffusion : diffusion.c
	$(CC) $(CFLAGS) -o $@ $<

test:
	tar -czvf diffusion.tar.gz diffusion.c diffusion.cl makefile
	/home/hpc2021/diffusion_opencl/check_submission.py diffusion.tar.gz

clean:
	rm -rf $(BINS) diffusion.tar.gz ./extracted/