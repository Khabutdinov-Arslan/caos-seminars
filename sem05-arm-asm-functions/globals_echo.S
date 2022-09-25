    .data
    .global R
R:  .space 8 // allocate 8 zeroed bytes

    .text
    .global calculate

calculate:
    adr x0, .Lexterns // get adress of Lexterns to x0
    ldr x1, [x0, 8]
    ldr x1, [x1]
    ret
    str x0, [x1]
    ret

.Lexterns:
    .quad A
