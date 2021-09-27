	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O0
	.text
	.section	.rodata
.LC0:
	.string	"%lld"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movl	%edi, -20(%rbp)	# argc, argc
	movq	%rsi, -32(%rbp)	# argv, argv
# proj1.c:13:     long long sum = 0;
	movq	$0, -16(%rbp)	#, sum
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	movl	$0, -4(%rbp)	#, a
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	jmp	.L2	#
.L3:
# proj1.c:16:         sum += a;
	movl	-4(%rbp), %eax	# a, tmp85
	cltq
	addq	%rax, -16(%rbp)	# _1, sum
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	addl	$1, -4(%rbp)	#, a
.L2:
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	cmpl	$1000000000, -4(%rbp)	#, a
	jle	.L3	#,
# proj1.c:17:     printf("%lld", sum);
	movq	-16(%rbp), %rax	# sum, tmp86
	movq	%rax, %rsi	# tmp86,
	movl	$.LC0, %edi	#,
	movl	$0, %eax	#,
	call	printf	#
# proj1.c:19:     return 0;
	movl	$0, %eax	#, _8
# proj1.c:20: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.1 20210728 (Red Hat 11.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
