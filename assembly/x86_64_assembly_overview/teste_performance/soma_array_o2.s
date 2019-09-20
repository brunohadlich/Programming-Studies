	.file	"soma_array.c"
	.text
	.p2align 4,,15
	.globl	soma_array
	.type	soma_array, @function
soma_array:
.LFB0:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L4
	leal	-1(%rsi), %eax
	leaq	4(%rdi,%rax,4), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movslq	(%rdi), %rdx
	addq	$4, %rdi
	addq	%rdx, %rax
	cmpq	%rcx, %rdi
	jne	.L3
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	soma_array, .-soma_array
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
