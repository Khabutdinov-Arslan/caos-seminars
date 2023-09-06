    .intel_syntax noprefix
    .text
    .global sum

sum: // rdi = n
    mov rsi, 0 // i = 0
    mov rax, 0 // sum = 0
loop:
    add rsi, 1 // i += 1
    add rax, rsi
    cmp rsi, rdi // i < n
    jl loop
    ret
