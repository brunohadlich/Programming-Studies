	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp

	leal (%rdx,%rax), %ebx
	lea (%rdx,%rax), %ebx

	mov -16(%rbp), %eax


	mov -16(%rbp), %al
	movb -16(%rbp), %al
	mov -16(%rbp), %ah
	movb -16(%rbp), %ah
	mov -16(%rbp), %ax
	movw -16(%rbp), %ax
	mov -16(%rbp), %eax
	movl -16(%rbp), %eax
	mov -16(%rbp), %rax
	movq -16(%rbp), %rax


	add    $3, %al
	addb    $3, %al
	add    $3, %ah
	addb    $3, %ah
	add    $3, %ax
	addw    $3, %ax
	add    $3, %eax
	addl    $3, %eax
	add    $3, %rax
	addq    $3, %rax

	add    $0b11000011110, %ax
	add    $0b1, %ax
	add    $0123, %ax
	add    $123, %ax
	add    $0x123, %ax

	mov (%rbp), %eax
	mov -16(%rbp), %eax

	mov (%rbp, %rsi), %eax
	mov -16(%rbp, %rsi), %eax

	mov (%rbp, %rsi, 4), %eax
	mov -16(%rbp, %rsi, 4), %eax

	mov (, %rsi, 4), %eax
	mov -16(, %rsi, 4), %eax

	mov (, %rsi), %eax
	mov -16(, %rsi), %eax

	mov (-16), %eax

	mov %cs:16(, %rsi, 4), %eax
	mov %ds:16(, %rsi, 4), %eax
	mov %ss:16(, %rsi, 4), %eax
	mov %es:16(, %rsi, 4), %eax
	mov %fs:16(, %rsi, 4), %eax
	mov %gs:16(, %rsi, 4), %eax


	mov -16(%rbp, %rsi, 4), %eax
	mov -16(%rsp, %rsi, 4), %eax
	mov -16(%rsi, %rsi, 4), %eax
	mov -16(%rdi, %rsi, 4), %eax
	mov -16(%rax, %rsi, 4), %eax
	mov -16(%rbx, %rsi, 4), %eax
	mov -16(%rcx, %rsi, 4), %eax
	mov -16(%rdx, %rsi, 4), %eax

	mov -16(%r8, %rsi, 4), %eax
	mov -16(%r9, %rsi, 4), %eax
	mov -16(%r10, %rsi, 4), %eax
	mov -16(%r11, %rsi, 4), %eax
	mov -16(%r12, %rsi, 4), %eax
	mov -16(%r13, %rsi, 4), %eax
	mov -16(%r14, %rsi, 4), %eax
	mov -16(%r15, %rsi, 4), %eax

	mov -16(%r15, %rbp, 4), %eax
	#mov -16(%r15, %rsp, 4), %eax
	mov -16(%r15, %rsi, 4), %eax
	mov -16(%r15, %rsi, 4), %eax
	mov -16(%r15, %rdi, 4), %eax
	mov -16(%r15, %rax, 4), %eax
	mov -16(%r15, %rbx, 4), %eax
	mov -16(%r15, %rcx, 4), %eax
	mov -16(%r15, %rdx, 4), %eax

	mov (0x45), %rax

	mov %cs:-16(%rbp, %rsi, 4), %eax
	addl %eax, %ebx
	shufps $0x1b, %xmm0, %xmm0

	addl %eax, %edx
	addq -8(%rbp), %rbx
	push %rcx
	push -8(%rbp)
	push $37
popq %rbp
popq -12(%rbp)



	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
