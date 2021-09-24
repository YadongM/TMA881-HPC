.PHONY : all
all : proj1.s proj1

proj1.s : proj1.c
	gcc -S -fverbose-asm $<

proj1 : proj1.c
	gcc -o $@ $< -O0 -g


.PHONY : clean
clean :
	rm -f proj1.s $(BINS)
