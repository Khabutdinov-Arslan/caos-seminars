agcc := /opt/aarch64-gcc/bin/aarch64-linux-gnu-gcc

sections:
	$(agcc) sections.c -o sections.out

globals_echo:
	$(agcc) globals_echo.c globals_echo.S -o globals_echo.out

int_echo:
	$(agcc) int_echo.S -o int_echo.out

structs:
	$(agcc) structs.c -o structs.out

clean:
	rm *.out
