    .intel_syntax noprefix
    .text
    .global get

get:
    mov eax, [rdi + rsi * 4]
    ret
