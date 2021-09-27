	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%lld"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# proj1.c:17:     printf("%lld", sum);
	movl	$.LC0, %edi	#,
	xorl	%eax, %eax	#
	movabsq	$500000000500000000, %rsi	#, tmp85
	call	printf	#
# proj1.c:20: }
	xorl	%eax, %eax	#
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.1 20210728 (Red Hat 11.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
