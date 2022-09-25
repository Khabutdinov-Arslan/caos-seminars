agcc := /opt/aarch64-gcc/bin/aarch64-linux-gnu-gcc

globals_echo:
	$(agcc) globals_echo.c globals_echo.S -o globals_echo.out

int_echo:
	$(agcc) int_echo.S -o int_echo.out

clean:
	rm *.out
