SHELL:=/bin/bash

stack:
	gcc -m64 -z execstack -fno-stack-protector stack/stack_overflow.c

heap:
	gcc -m64 -z execstack -fno-stack-protector heap/heap_overflow.c

hello:
	gcc -c shellcode/helloworld.s -o bin/helloworld.o
	ld -o bin/helloworld bin/helloworld.o
	objcopy -O binary --only-section=.text bin/helloworld.o bin/helloworld.sc

shell:
	gcc -c shellcode/shell.s -o bin/shell.o
	ld -o bin/shell bin/shell.o
	objcopy -O binary --only-section=.text bin/shell.o bin/shell.sc

