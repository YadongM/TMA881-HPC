	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O1
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
	movq	%rax, %rbx	# tmp97, start
	movl	$1000000001, %eax	#, ivtmp_1
.L2:
# proj1.c:18:     for (a = 0; a <= 1000000000; ++a)
	subl	$1, %eax	#, ivtmp_1
	jne	.L2	#,
# proj1.c:20:     printf("Sum = %lld\n", sum);
	movabsq	$500000000500000000, %rsi	#, tmp91
	movl	$.LC0, %edi	#,
	movl	$0, %eax	#,
	call	printf	#
# proj1.c:22:     stop = clock();
	call	clock	#
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	subq	%rbx, %rax	# start, tmp92
# proj1.c:23:     double duration = ((double)(stop - start)/CLOCKS_PER_SEC);
	pxor	%xmm0, %xmm0	# tmp93
	cvtsi2sdq	%rax, %xmm0	# tmp92, tmp93
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
