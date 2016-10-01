.section .text
.global _start

_start:
	jmp string

code:
	# Following subtractions are to avoid NULL bytes in binary
	pop %rsi
	mov $0x11111112, %rax
	sub $0x11111111, %rax	# 1 -> syscall -> write()
	mov $0x11111112, %rdi
	sub $0x11111111, %rdi	# write(1, ...
	mov $0x1111111F, %rdx
	sub $0x11111111, %rdx
	syscall				# interrupt 80 -> syscall
	# write(1, $rsi, 14) -> man 2 write

	mov $0x1111114D, %rax
	sub $0x11111111, %rax			# subtract to get 60 -> exit()
	xor %rdi, %rdi				# zero out rdi for exit(0)
	syscall					# interrupt 80 -> syscall
	# exit(0) -> man 2 exit

string:
	# I act as a buffer so the jmp-call combo can do its magic
	call code
	.ascii "Hello, world!\n"

