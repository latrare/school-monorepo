SHELL:=/bin/bash

all:

clean:
	find . -type f -name '*.o' | xargs rm -vf
	rm -vf bin/*

stack: bin/stack_overflow
heap: bin/heap_overflow

bin/stack_overflow: stack/stack_overflow.c
	gcc -m64 -z execstack -fno-stack-protector stack/stack_overflow.c -o bin/stack_overflow

bin/heap_overflow: heap/heap_overflow.c
	gcc -m64 -z execstack -fno-stack-protector heap/heap_overflow.c -o bin/heap_overflow

hello: shellcode/helloworld.s
	gcc -c shellcode/helloworld.s -o bin/helloworld.o
	ld -o bin/helloworld bin/helloworld.o
	objcopy -O binary --only-section=.text bin/helloworld.o bin/helloworld.sc

shell: shellcode/shell.s
	gcc -c shellcode/shell.s -o bin/shell.o
	ld -o bin/shell bin/shell.o
	objcopy -O binary --only-section=.text bin/shell.o bin/shell.sc

