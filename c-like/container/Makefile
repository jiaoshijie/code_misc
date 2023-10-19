V := @

run: build
	$(V)./test

build:
	$(V)c++ test.cpp -g -o test

debug: build
	$(V)gdb -q test

clean:
	$(V)rm -rf test
