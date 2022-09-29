    .section .text
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
    // prepare arguments and call: scanf(x0: "%d", x1: &val1)
    adr x0, format_string_scanf
    sub sp, sp, 16 // 12 extra bytes to keep stack 16-byte aligned
    mov x1, sp
    push x1
    push x30 // original return adress must be preserved because it will be overwriten by next command
    bl scanf
    pop x30
    pop x1

    ldr x1, [x1]

    // prepare arguments and call: printf(x0: "%d\n", x1: val1)
    adr x0, format_string_printf
    sub sp, sp, 8 // extra bytes to keep stack 16-byte aligned
    push x30
    bl printf
    pop x30

    // add sp, sp, 32 // return stack pointer to original position
    mov x0, 0
    ret
    
    .section    .rodata // section for global constants
format_string_printf:
    .string  "%d\n"
format_string_scanf:    
    .string  "%d"
