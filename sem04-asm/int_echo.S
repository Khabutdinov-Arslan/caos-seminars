    .intel_syntax noprefix
    .text
    .global main

// stack needs to be 16-byte aligned before `call`
// 8 bytes are taken by rtuen address
main:
   sub rsp, 16 // allocate space for int
   mov rdi, offset format_string_scanf
   mov rsi, rsp
   push rsi // save scratch register on stack
   call scanf
   pop rsi
   mov rsi, [rsi]
   add rsp, 8
   mov rdi, offset format_string_printf
   call printf
   add rsp, 8
   ret


.data // section for global constants
format_string_printf:
    .string  "%d\n"
format_string_scanf:    
    .string  "%d"
