.PHONY : all
all : proj1O0.s proj1O1.s proj1O2.s proj1O3.s proj1Os.s proj1Og.s \
      proj1

proj1O0.s : proj1.c
	gcc -S -fverbose-asm $< -O0 -o $@


proj1O1.s : proj1.c
	gcc -S -fverbose-asm $< -O1 -o $@

proj1O2.s : proj1.c
	gcc -S -fverbose-asm $< -O2 -o $@

proj1O3.s : proj1.c
	gcc -S -fverbose-asm $< -O3 -o $@


proj1Os.s : proj1.c
	gcc -S -fverbose-asm $< -Os -o $@

proj1Og.s : proj1.c
	gcc -S -fverbose-asm $< -Og -o $@



proj1 : proj1.c
	gcc -o $@ $< -O0 -g


valgrind_test : vandg.c
	gcc -o $@ $< -Oo -g













.PHONY : clean
clean :
	rm -f proj1* $(BINS)
