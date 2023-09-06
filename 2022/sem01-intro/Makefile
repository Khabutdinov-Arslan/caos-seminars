preprocess:
	gcc -E aplusb.c -o aplusb_preprocessed.c
compile: preprocess
	gcc -S aplusb_preprocessed.c -o aplusb_asm.S
object: compile
	gcc -c aplusb_asm.S -o aplusb_object.o
binary: object
	gcc aplusb_object.o -o aplusb_executable.out
sum: sum_lib.c sum_lib.h
	gcc -g sum_lib.c -o sum.out
bad_gdb: bad.c
	gcc -g bad.c -o bad.out
bad_asan:
	gcc -fsanitize=address -g bad.c -o bad.out
clean:
	rm aplusb_object.o aplusb_executable.out sum.out bad.out coredump
