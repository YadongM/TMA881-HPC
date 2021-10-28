CC := gcc
BINS = diffusion
CFLAGS = -O2

.PHONY : all
all : $(BINS) 

diffusion : diffusion.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BINS) 