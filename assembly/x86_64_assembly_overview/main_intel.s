	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp

	mov eax, DWORD PTR -16[rbp]
	mov eax, -16[rbp]

	mov eax, gs:16[rbp + rsi * 4]

	mov al, BYTE PTR -16[rbp]
	movb al, BYTE PTR -16[rbp]
	mov ah, BYTE PTR -16[rbp]
	movb ah, BYTE PTR -16[rbp]
	mov ax, WORD PTR -16[rbp]
	movw ax, WORD PTR -16[rbp]
	mov eax, DWORD PTR -16[rbp]
	#movl eax, DWORD PTR -16[rbp]
	mov rax, QWORD PTR -16[rbp]
	#movq rax, QWORD PTR -16[rbp]
	add    eax, 3
	addw    ax, 3
	mov eax, gs:-16[rbp + rsi * 4]

	.cfi_def_cfa_register 6
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
