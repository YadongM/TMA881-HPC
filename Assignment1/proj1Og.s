	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -Og
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Sum = %lld\n"
.LC2:
	.string	"Time cost = %lf s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
# proj1.c:16:     start = clock();
	call	clock	#
	movq	%rax, %rbx	# tmp96, start
# proj1.c:13:     long long sum = 0;
	movl	$0, %esi	#, sum
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	movl	$0, %eax	#, a
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	jmp	.L2	#
.L3:
# proj1.c:19:         sum += a;
	movslq	%eax, %rdx	# a, a
	addq	%rdx, %rsi	# a, sum
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	addl	$1, %eax	#, a
.L2:
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	cmpl	$1000000000, %eax	#, a
	jle	.L3	#,
# proj1.c:20:     printf("Sum = %lld\n", sum);
	movl	$.LC0, %edi	#,
	movl	$0, %eax	#,
	call	printf	#
# proj1.c:22:     stop = clock();
	call	clock	#
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	subq	%rbx, %rax	# start, _2
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	pxor	%xmm0, %xmm0	# _3
	cvtsi2sdq	%rax, %xmm0	# _2, _3
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	divsd	.LC1(%rip), %xmm0	#, duration
# proj1.c:25:     printf("Time cost = %lf s\n", duration);
	movl	$.LC2, %edi	#,
	movl	$1, %eax	#,
	call	printf	#
# proj1.c:27: }
	movl	$0, %eax	#,
	popq	%rbx	#
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 11.2.1 20210728 (Red Hat 11.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
