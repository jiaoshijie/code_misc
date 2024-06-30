V := @

run: compile
	$(V)./a.out

compile:
	$(V)c++ `pkg-config  --cflags --libs python3-embed` main.cpp

clean:
	$(V)rm -f ./a.out
