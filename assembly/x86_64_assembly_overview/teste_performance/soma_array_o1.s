	.file	"soma_array.c"
	.text
	.globl	soma_array
	.type	soma_array, @function
soma_array:
.LFB0:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L4
	movq	%rdi, %rdx
	leal	-1(%rsi), %eax
	leaq	4(%rdi,%rax,4), %rsi
	movl	$0, %eax
.L3:
	movslq	(%rdx), %rcx
	addq	%rcx, %rax
	addq	$4, %rdx
	cmpq	%rsi, %rdx
	jne	.L3
	ret
.L4:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	soma_array, .-soma_array
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
