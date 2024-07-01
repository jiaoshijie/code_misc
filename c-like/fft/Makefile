V := @

run: compile
	$(V)./a.out

compile:
	$(V)c++ main.cpp `pkg-config --cflags python3-embed` `python3-config --ldflags --embed` -g

clean:
	$(V)rm -f ./a.out
