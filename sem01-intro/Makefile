preprocess: aplusb.c
	gcc -E aplusb.c -o aplusb_preprocessed.c
compile: preprocess
	gcc -S aplusb_preprocessed.c -o aplusb_asm.S
object: compile
	gcc -c aplusb_asm.S -o aplusb_object.o
binary: object
	gcc aplusb_object.o -o aplusb_executable.out
debug: aplusb.c
	gcc -g aplusb.c -o aplusb_debug.out
bad_gdb: bad.c
	gcc -g bad.c -o bad.out
bad_asan:
	gcc -fsanitize=address -g bad.c -o bad.out
clean:
	rm aplusb_object.o aplusb_executable.out aplusb_debug.out bad.out coredump
