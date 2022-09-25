    .text
    .global get
get:
    mov x3, 4 // sz = 4
    mul x2, x1, x3 // off = idx * sz
    ldr x0, [x0, x2] // ret = *(arr + off)
    ret
