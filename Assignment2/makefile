BINS = cell_distances_baseline cell_distances
CFLAGS = -O2 -fopenmp -lm

.PHONY : all
all : $(BINS) 

cell_distances_baseline : cell_distances.c
	gcc $(CFLAGS) -o $@ $<

cell_distances : cell_distances_para.c
	gcc $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	rm -rf $(BINS)
