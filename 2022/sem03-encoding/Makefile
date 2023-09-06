print_int.out: print_int.c
	gcc print_int.c -o print_int.out
print_float.out: print_float.c
	gcc print_float.c -o print_float.out
overflow.out: overflow.c
	gcc -fsanitize=undefined overflow.c -o overflow.out
print_union.out: print_union.c
	gcc print_union.c -o print_union.out
clean:
	rm *.out