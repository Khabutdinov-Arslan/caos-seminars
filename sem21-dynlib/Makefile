static:
	gcc foo.c main.c -o static.out

dynamic:
	gcc -fPIC -shared foo.c -o libfoo.so
	gcc -L . main.c -lfoo -o dynamic.out

loader: dynamic
	gcc loader.c -ldl -o loader.out

mmap_loader: dynamic
	gcc mmap_loader.c -ldl -o mmap_loader.out

clean:
	rm *.out
