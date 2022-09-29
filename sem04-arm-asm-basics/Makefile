agcc := /opt/aarch64-gcc/bin/aarch64-linux-gnu-gcc

sum_demo:
	$(agcc) sum.c -o sum.out

arr_get:
	$(agcc) arr_get.c arr_get.S -o arr_get.out

sum_asm:
	$(agcc) sum_main.c sum_fun.S -o sum_ext.out

sum_n_asm:
	$(agcc) sum_n.c sum_n.S -o sum_n.out

clean:
	rm *.out
