agcc := /opt/aarch64-gcc/bin/aarch64-linux-gnu-gcc

arr_get.out: arr_get.c arr_get.S
	$(agcc) arr_get.c arr_get.S -o arr_get.out
sum_n.out: sum_n.c sum_n.S
	$(agcc) sum_n.c sum_n.S -o sum_n.out
int_echo.out: int_echo.S
	$(agcc) int_echo.S -o int_echo.out
clean:
	rm *.out
