.PHONY : all
all : proj1O0.s proj1O1.s proj1O2.s proj1O3.s proj1Os.s proj1Og.s \
      proj1 valgrind_test gdb_test same_file different_file inlined_manually \
	  locality_row_O0 locality_row_O2 locality_row_O2n locality_col_O0 locality_col_O2 locality_col_O2n\



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


valgrind_test : valgrind_test.c
	gcc -o $@ $< -O0 -g

gdb_test : gdb_test.c
	gcc -o $@ $< -O0 -g

same_file : same_file.c
	gcc -o $@ $< -O2

different_file : different_file.c different_file_mul.c
	gcc -o $@ $^ -O2

inlined_manually : inlined_manually.c
	gcc -o $@ $< -O2

locality_row_O0 : locality_row_sums.c
	gcc -o $@ $< -O0

locality_row_O2 : locality_row_sums.c
	gcc -o $@ $< -O2

locality_row_O2n : locality_row_sums.c
	gcc -o $@ $< -O2 -march=native

locality_col_O0 : locality_col_sums.c
	gcc -o $@ $< -O0

locality_col_O2 : locality_col_sums.c
	gcc -o $@ $< -O2

locality_col_O2n : locality_col_sums.c
	gcc -o $@ $< -O2 -march=native









.PHONY : clean
clean :
	rm -f proj1* $(BINS)
