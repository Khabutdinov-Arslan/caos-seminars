sum.out: sum.c
	gcc sum.c -o sum.out
arr_get.out: arr_get.c arr_get.S
	gcc arr_get.c arr_get.S -o arr_get.out
sum_n.out: sum_n.c sum_n.S
	gcc sum_n.c sum_n.S -o sum_n.out
int_echo.out: int_echo.S
	gcc -g -no-pie int_echo.S -o int_echo.out
exp.out:
	gcc exp.c exp.S -o exp.out
add.out:
	gcc add.c add.S -o add.out
add_int.out:
	gcc -mavx add_int.c -o add_int.out
clean:
	rm *.out
