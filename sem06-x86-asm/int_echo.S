    .intel_syntax noprefix
    .text
    .global main

// stack needs to be 16-byte aligned before `call`
// but it is now aligned because call it pushed old rsp
main:
   sub rsp, 16
   mov rdi, offset format_string_scanf
   mov rsi, rsp
   push rsi // need to be 16-aligned before this call
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
