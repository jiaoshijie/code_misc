V := @

CHead := ./head
Source := array.c
Rundir := ./bin/
Runable := $(basename $(Source))
Gasfile := $(addsuffix .S,$(basename $(Source)))

CC := gcc -m32 -I $(CHead)
GDB := gdb -q -x ./tools/gdbinit

run: build
	$(V)$(Rundir)$(Runable)

build: $(Source)
	$(V)mkdir -p $(Rundir)
	$(V)$(CC) -o $(Rundir)$(Runable) $^

debug: $(Source)
	$(V)mkdir -p $(Rundir)
	$(V)$(CC) -o $(Rundir)$(Runable) -g $^
	$(V)$(GDB) $(Rundir)$(Runable)

gas: $(Source)
	$(V)$(CC) -o $(Gasfile) -S $^

clean:
	$(V)rm -rf $(Rundir)
