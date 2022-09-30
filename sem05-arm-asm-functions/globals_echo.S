    .data
    .global R
R:  .space 8 // allocate 8 zeroed bytes

    .text
    .global calculate

calculate:
    ldr x1, =A
    ldr x2, =R
    ldr x1, [x1] // A
    str x1, [x2] // *R = A
    ret
