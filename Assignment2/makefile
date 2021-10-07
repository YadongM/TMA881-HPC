BINS = cell_distances
CFLAGS = -O2 -fopenmp -lm

.PHONY : all
all : $(BINS) 

cell_distances : cell_distances.c
	gcc $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	rm -rf $(BINS)