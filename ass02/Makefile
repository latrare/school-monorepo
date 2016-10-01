SHELL:=/bin/bash

clean:
	find . -type f -name '*.o' | xargs rm -vf
	rm -vf bin/*

stack:
	gcc -m64 -z execstack -fno-stack-protector stack/stack_overflow.c -o bin/stack_overflow

heap:
	gcc -m64 -z execstack -fno-stack-protector heap/heap_overflow.c -o bin/stack_overflow

hello:
	gcc -c shellcode/helloworld.s -o bin/helloworld.o
	ld -o bin/helloworld bin/helloworld.o
	objcopy -O binary --only-section=.text bin/helloworld.o bin/helloworld.sc

shell:
	gcc -c shellcode/shell.s -o bin/shell.o
	ld -o bin/shell bin/shell.o
	objcopy -O binary --only-section=.text bin/shell.o bin/shell.sc

