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
	cmpl	$6, %eax
	jbe	.L8
	movl	%esi, %edx
	movq	%rdi, %rax
	vpxor	%xmm0, %xmm0, %xmm0
	shrl	$3, %edx
	salq	$5, %rdx
	addq	%rdi, %rdx
	.p2align 4,,10
	.p2align 3
.L4:
	vpmovsxdq	(%rax), %ymm1
	vmovdqu	(%rax), %ymm2
	addq	$32, %rax
	vpaddq	%ymm0, %ymm1, %ymm1
	vextracti128	$0x1, %ymm2, %xmm0
	vpmovsxdq	%xmm0, %ymm0
	vpaddq	%ymm1, %ymm0, %ymm0
	cmpq	%rdx, %rax
	jne	.L4
	vmovdqa	%xmm0, %xmm1
	vextracti128	$1, %ymm0, %xmm0
	movl	%esi, %edx
	vpaddq	%xmm0, %xmm1, %xmm0
	andl	$-8, %edx
	vpsrldq	$8, %xmm0, %xmm1
	vpaddq	%xmm1, %xmm0, %xmm0
	vmovq	%xmm0, %rax
	cmpl	%edx, %esi
	je	.L13
	vzeroupper
.L3:
	movslq	%edx, %rcx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	leal	1(%rdx), %ecx
	cmpl	%ecx, %esi
	jle	.L11
	movslq	%ecx, %rcx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	leal	2(%rdx), %ecx
	cmpl	%ecx, %esi
	jle	.L11
	movslq	%ecx, %rcx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	leal	3(%rdx), %ecx
	cmpl	%ecx, %esi
	jle	.L11
	movslq	%ecx, %rcx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	leal	4(%rdx), %ecx
	cmpl	%ecx, %esi
	jle	.L11
	movslq	%ecx, %rcx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	leal	5(%rdx), %ecx
	cmpl	%ecx, %esi
	jle	.L11
	movslq	%ecx, %rcx
	addl	$6, %edx
	movslq	(%rdi,%rcx,4), %rcx
	addq	%rcx, %rax
	cmpl	%edx, %esi
	jle	.L11
	movslq	%edx, %rdx
	movslq	(%rdi,%rdx,4), %rdx
	addq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	xorl	%eax, %eax
.L11:
	ret
	.p2align 4,,10
	.p2align 3
.L13:
	vzeroupper
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
