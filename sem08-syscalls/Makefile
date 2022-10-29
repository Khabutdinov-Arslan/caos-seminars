hello_stdlib:
	gcc hello_stdlib.c -o hello_stdlib.out
hello_stdlib_static:
	gcc -static hello_stdlib.c -o hello_stdlib_static.out
hello_syscall:
	gcc -nostdlib hello_syscall.c syscall.S -o hello_syscall.out
hello_nostdlib:
	gcc -no-pie -nostdlib hello_nostdlib.S -o hello_nostdlib.out
clean:
	rm *.out
