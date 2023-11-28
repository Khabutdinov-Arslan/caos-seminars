static.out:
	gcc foo.c main.c -o static.out

libfoo.so:
	gcc -fPIC -shared foo.c -o libfoo.so

dynamic.out: libfoo.so
	gcc -L . main.c -lfoo -o dynamic.out

dynamic_rpath.out: libfoo.so
	gcc -L. main.c -lfoo -Wl,-rpath -Wl,'$$ORIGIN/.' -o dynamic_rpath.out

loader.out: dynamic.out
	gcc loader.c -ldl -o loader.out

mmap_loader.out: dynamic.out
	gcc mmap_loader.c -ldl -o mmap_loader.out

clean:
	rm *.out
	rm *.so
