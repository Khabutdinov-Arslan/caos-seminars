    .data
    .global R
R:  .space 8 // allocate 8 zeroed bytes

    .text
    .global calculate

calculate:
    adr x0, .Lexterns // get adress of Lexterns to x0
    ldr x1, [x0] // &A
    ldr x2, [x0, 8] // &R
    ldr x1, [x1] // A
    str x1, [x2] // *R = A
    ret

.Lexterns:
    .quad A
    .quad R
