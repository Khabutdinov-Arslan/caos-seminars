    .intel_syntax noprefix
    .text
    .global get

get: // clang made me do it because if you have function ret you may have preprocessing conflict
    mov eax, [rdi + rsi * 4]
    ret
