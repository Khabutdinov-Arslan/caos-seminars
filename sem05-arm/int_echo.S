    .text
    .global main

    .macro push Rn:req
      sub sp, sp, 8
      str \Rn, [sp]    
    .endm

    .macro pop Rn:req
      ldr \Rn, [sp]
      add sp, sp, 8
    .endm
    
main:
    sub sp, sp, 16 // 12 extra bytes to keep stack 16-byte aligned
    adr x0, format_string_scanf
    mov x1, sp
    push x1
    push x30 // save return address, because bl overwrites it
    bl scanf
    pop x30
    pop x1

    ldr x1, [x1]

    adr x0, format_string_printf
    add sp, sp, 8 // extra bytes to keep stack 16-byte aligned
    push x30
    bl printf
    pop x30

    add sp, sp, 8
    mov x0, 0
    ret
    
.data // section for global constants
format_string_printf:
    .string  "%d\n"
format_string_scanf:    
    .string  "%d"
