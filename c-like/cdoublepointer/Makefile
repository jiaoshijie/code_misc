V := @

Source := doublepointer.c

Head := ./head
Runable := $(basename $(Source))
RunDir := ./bin/

# -m32 32位程序
CC := gcc -m32 -o $(RunDir)$(Runable) -I $(Head)
GDB := gdb -q

run: build
	$(V)$(RunDir)$(Runable)

build: $(Source)
	mkdir -p $(RunDir)
	$(V)$(CC) $^

debug: argc.c
	$(V)$(CC) -g $^
	$(V)$(GDB) $(RunDir)$(Runable)

clean:
	$(V)rm -rf $(RunDir)
