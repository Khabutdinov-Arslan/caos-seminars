    .intel_syntax noprefix
    .text
    .global my_exp

my_exp:
    movsd xmm1, xmm0 // preserve x
    vxorpd xmm0, xmm0, xmm0 // clean result
    mov rax, 1
    cvtsi2sd xmm2, rax // x^n
    cvtsi2sd xmm5, rax // n!
    mov rax, 0 // i
    mov rdi, 10 // iteration_count
.Loop:
    vmovsd xmm4, xmm4, xmm2 // x^n
    vdivsd xmm4, xmm4, xmm5 // x^n/n!
    vaddsd xmm0, xmm0, xmm4 // res += x^n/n!

    vmulsd xmm2, xmm2, xmm1 // x^(n-1)*x
    add rax, 1 // i++
    cvtsi2sd xmm6, rax
    vmulsd xmm5, xmm5, xmm6 // (n-1)! * n

    cmp rax, rdi
    jl .Loop
.Finalize:
    ret
