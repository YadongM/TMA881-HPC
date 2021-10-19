BINS = newton
OBJS = main.o write_thrd.o compute_thrd.o
CFLAGS = -O2 -lpthread

.PHONY : all
all : $(BINS) 

newton : $(OBJS)
	gcc $(CFLAGS) -o $@ $^

main.o : main.c write_thrd.h compute_thrd.h common.h

write_thrd.o : write_thrd.c write_thrd.h common.h

compute_thrd.o : compute_thrd.c compute_thrd.h common.h

.PHONY : clean
clean :
	rm -rf $(BINS)
	rm -rf $(OBJS)
	rm -rf *.ppm
	rm -rf submission.tar.gz
	rm -rf extracted pictures
