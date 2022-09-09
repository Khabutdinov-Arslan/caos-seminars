preprocess:
	gcc -E aplusb.c -o aplusb_preprocessed.c
compile: aplusb_preprocessed.c
	gcc -S aplusb_preprocessed.c -o aplusb_asm.S
object: aplusb_asm.S
	gcc -c aplusb_asm.S -o aplusb_object.o
binary: aplusb_object.o
	gcc aplusb_object.o -o aplusb_executable.out
sum: sum_lib.c sum_lib.h
	gcc sum_lib.c -o sum.out
bad_gdb: bad.c
	gcc -g bad.c -o bad.out
bad_asan:
	gcc -fsanitize=address bad.c -o bad.out
