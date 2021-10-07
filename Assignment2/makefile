BINS = cell_distances cell_distances_serial
CFLAGS = -O2 -fopenmp -lm

.PHONY : all
all : $(BINS) 

cell_distances : cell_distances.c
	gcc $(CFLAGS) -o $@ $<

cell_distances_serial : cell_distances_para.c
	gcc $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	rm -rf $(BINS)