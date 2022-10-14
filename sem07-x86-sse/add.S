    .global very_important_function
    .intel_syntax noprefix
    .text

// (N=rdi, *A=rsi, *B=rdx, *R=rcx)
very_important_function:
    
    vxorps ymm2, ymm2, ymm2
    mov r8, rdi

    .Loop:
        sub rdi, 8
        
        vmovaps ymm0, [rsi + rdi * 4]
        vmovaps ymm1, [rdx + rdi * 4]
        vaddps ymm0, ymm0, ymm1
        vmovaps [rcx + rdi * 4], ymm0
        
        cmp rdi, 0
        jg .Loop

    ret
