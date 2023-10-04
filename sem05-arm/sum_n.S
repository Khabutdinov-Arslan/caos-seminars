    .text
    .global sum

sum:
    mov x1, x0 // limit = n
    mov x2, 0 // i = 0
    mov x0, 0 // sum = 0
loop:
    add x2, x2, 1 // i += 1
    add x0, x0, x2 // sum += i
    cmp x2, x1 // i < n
    blt loop
    ret
