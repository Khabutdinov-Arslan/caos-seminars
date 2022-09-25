.text // begin section with program scope
.global sum // label is visible outside this source

sum:
    add x2, x1, x0
    mov x0, x2 // int return value from function is passed in x0
    ret // return to main program
