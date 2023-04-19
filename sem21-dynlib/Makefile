static:
	gcc foo.c main.c -o static.out

shared_lib:
	gcc -fPIC -shared foo.c -o libfoo.so

dynamic: shared_lib
	gcc -L . main.c -lfoo -o dynamic.out

dynamic_rpath: shared_lib
	gcc -L. main.c -lfoo -Wl,-rpath -Wl,'$$ORIGIN/.' -o dynamic_rpath.out

loader: dynamic
	gcc loader.c -ldl -o loader.out

mmap_loader: dynamic
	gcc mmap_loader.c -ldl -o mmap_loader.out

clean:
	rm *.out, *.so
