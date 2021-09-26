	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O0
	.text
	.section	.rodata
.LC0:
	.string	"Sum = %lld\n"
.LC2:
	.string	"Time cost = %lf s\n"
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
	subq	$64, %rsp	#,
	movl	%edi, -52(%rbp)	# argc, argc
	movq	%rsi, -64(%rbp)	# argv, argv
# proj1.c:13:     long long sum = 0;
	movq	$0, -16(%rbp)	#, sum
# proj1.c:16:     start = clock();
	call	clock	#
	movq	%rax, -24(%rbp)	# tmp87, start
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	movl	$0, -4(%rbp)	#, a
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	jmp	.L2	#
.L3:
# proj1.c:19:         sum += a;
	movl	-4(%rbp), %eax	# a, tmp88
	cltq
	addq	%rax, -16(%rbp)	# _1, sum
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	addl	$1, -4(%rbp)	#, a
.L2:
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	cmpl	$1000000000, -4(%rbp)	#, a
	jle	.L3	#,
# proj1.c:20:     printf("Sum = %lld\n", sum);
	movq	-16(%rbp), %rax	# sum, tmp89
	movq	%rax, %rsi	# tmp89,
	movl	$.LC0, %edi	#,
	movl	$0, %eax	#,
	call	printf	#
# proj1.c:22:     stop = clock();
	call	clock	#
	movq	%rax, -32(%rbp)	# tmp90, stop
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	movq	-32(%rbp), %rax	# stop, tmp91
	subq	-24(%rbp), %rax	# start, _2
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	pxor	%xmm0, %xmm0	# _3
	cvtsi2sdq	%rax, %xmm0	# _2, _3
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	movsd	.LC1(%rip), %xmm1	#, tmp93
	divsd	%xmm1, %xmm0	# tmp93, tmp92
	movsd	%xmm0, -40(%rbp)	# tmp92, duration
# proj1.c:25:     printf("Time cost = %lf s\n", duration);
	movq	-40(%rbp), %rax	# duration, tmp94
	movq	%rax, %xmm0	# tmp94,
	movl	$.LC2, %edi	#,
	movl	$1, %eax	#,
	call	printf	#
# proj1.c:26:     return 0;
	movl	$0, %eax	#, _16
# proj1.c:27: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 11.2.1 20210728 (Red Hat 11.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
