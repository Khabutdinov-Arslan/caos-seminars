    .intel_syntax noprefix
    .text
    .global main

main:
   mov rdi, offset format_string
   mov rsi, 42
   call printf


    .data
format_string:
    .string "%d"