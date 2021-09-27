	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -Og
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%lld"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# proj1.c:13:     long long sum = 0;
	movl	$0, %esi	#, sum
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	movl	$0, %eax	#, a
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	jmp	.L2	#
.L3:
# proj1.c:16:         sum += a;
	movslq	%eax, %rdx	# a, a
	addq	%rdx, %rsi	# a, sum
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	addl	$1, %eax	#, a
.L2:
# proj1.c:15:     for (a = 0; a <= 1000000000; ++a)
	cmpl	$1000000000, %eax	#, a
	jle	.L3	#,
# proj1.c:17:     printf("%lld", sum);
	movl	$.LC0, %edi	#,
	movl	$0, %eax	#,
	call	printf	#
# proj1.c:20: }
	movl	$0, %eax	#,
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.1 20210728 (Red Hat 11.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
