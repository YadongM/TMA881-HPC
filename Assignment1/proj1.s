	.file	"proj1.c"
# GNU C17 (GCC) version 11.2.1 20210728 (Red Hat 11.2.1-1) (x86_64-redhat-linux)
#	compiled by GNU C version 11.2.1 20210728 (Red Hat 11.2.1-1), GMP version 6.2.0, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64
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
	movl	%edi, -20(%rbp)	# argc, argc
	movq	%rsi, -32(%rbp)	# argv, argv
# proj1.c:11:   int a = 0;
	movl	$0, -4(%rbp)	#, a
# proj1.c:13:   if ( a == 1 )
	cmpl	$1, -4(%rbp)	#, a
	jne	.L2	#,
# proj1.c:14:     a = 2;
	movl	$2, -4(%rbp)	#, a
	jmp	.L3	#
.L2:
# proj1.c:15:   else if ( a == 0 )
	cmpl	$0, -4(%rbp)	#, a
	jne	.L3	#,
# proj1.c:16:     a = 3;
	movl	$3, -4(%rbp)	#, a
.L3:
# proj1.c:18:   return 0;
	movl	$0, %eax	#, _4
# proj1.c:19: }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.1 20210728 (Red Hat 11.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
