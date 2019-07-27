
section .text

	global init_module
	global cleanup_module
	global kernel_version

	extern printk

init_module:
	push	dword str1
	call	printk
	pop	rax
	xor	eax,eax
	ret

cleanup_module:
	push	dword str2
	call	printk
	pop	rax
	ret
	
str1		db	"init_module done",0xa,0
str2		db	"cleanup_module done",0xa,0

kernel_version	db	"5.0.0",0
