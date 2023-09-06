#include <sys/syscall.h>

	.text
	.intel_syntax noprefix
	.global _start

.data
	string: .ascii "Hello, World!"

.text
_start:

output:
	mov rax, SYS_write //use syscall write
	mov rdi, 1 //with stdout
	mov rsi, offset string //given string
	mov rdx, 13 //with given length
	syscall

exit:
	mov rax,SYS_exit //use exit syscall 
	mov rdi, 0 //code 0
	syscall
