V := @

static: archive
	$(V)gcc main.c -I ./ -L ./ -ljsjl -o demo

lib1-s:
	$(V)gcc jsj_lib1.c -c -o jsj_lib1.o

lib2-s:
	$(V)gcc jsj_lib2.c -c -o jsj_lib2.o

archive: lib1-s lib2-s
	$(V)ar rcs libjsjl.a jsj_lib1.o jsj_lib2.o

dynamic: so-d
	$(V)gcc main.c -I ./ -L ./ -ljsjl -o demo

run-dynamic: dynamic
	LD_LIBRARY_PATH=./ ./demo

lib1-d:
	$(V)gcc jsj_lib1.c -c -fPIC -o jsj_lib1.o

lib2-d:
	$(V)gcc jsj_lib2.c -c -fPIC -o jsj_lib2.o

so-d: lib1-d lib2-d
	$(V)gcc -shared -o libjsjl.so jsj_lib1.o jsj_lib2.o

ldconfig:
	sudo ldconfig -v

clean:
	rm -rf *.o *.a *.so demo
