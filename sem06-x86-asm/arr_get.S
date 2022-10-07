    .intel_syntax noprefix
    .text
    .global _get

_get: // clang made me do it because if you have function ret you may have preprocessing conflict
    mov eax, [rdi + rsi * 4]
    ret
