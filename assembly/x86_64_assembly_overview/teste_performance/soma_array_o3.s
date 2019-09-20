	.file	"soma_array.c"
	.text
	.p2align 4,,15
	.globl	soma_array
	.type	soma_array, @function
soma_array:
.LFB0:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L7
	leal	-1(%rsi), %eax
	cmpl	$2, %eax
	jbe	.L8
	movl	%esi, %edx
	pxor	%xmm0, %xmm0
	pxor	%xmm4, %xmm4
	movq	%rdi, %rax
	shrl	$2, %edx
	salq	$4, %rdx
	addq	%rdi, %rdx
	.p2align 4,,10
	.p2align 3
.L4:
	movdqu	(%rax), %xmm1
	movdqa	%xmm4, %xmm2
	addq	$16, %rax
	pcmpgtd	%xmm1, %xmm2
	movdqa	%xmm1, %xmm3
	punpckldq	%xmm2, %xmm3
	punpckhdq	%xmm2, %xmm1
	paddq	%xmm3, %xmm0
	paddq	%xmm1, %xmm0
	cmpq	%rdx, %rax
	jne	.L4
	movdqa	%xmm0, %xmm1
	movl	%esi, %edx
	psrldq	$8, %xmm1
	andl	$-4, %edx
	paddq	%xmm1, %xmm0
	movq	%xmm0, %rax
	cmpl	%edx, %esi
	je	.L11
.L3:
	movslq	%edx, %rcx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	leal	1(%rdx), %ecx
	cmpl	%ecx, %esi
	jle	.L1
	movslq	%ecx, %rcx
	addl	$2, %edx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	cmpl	%edx, %esi
	jle	.L1
	movslq	%edx, %rdx
	movslq	(%rdi,%rdx,4), %rdx
	addq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	xorl	%eax, %eax
.L1:
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	ret
.L8:
	xorl	%edx, %edx
	xorl	%eax, %eax
	jmp	.L3
	.cfi_endproc
.LFE0:
	.size	soma_array, .-soma_array
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
