CC := gcc
BINS = diffusion
CFLAGS = -O2 -lOpenCL

.PHONY : all
all : $(BINS) 

diffusion : diffusion.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BINS) 