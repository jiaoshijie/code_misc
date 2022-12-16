V := @

Source := main.c
Bin := demo
# HEAD := -I./head -I/usr/include/...
HEAD :=

CC := cc
CCARGV :=  -W -Wall -lX11
GDB := gdb -q -x ./tools/gdbinit

runAndclean: run clean

run: build
	$(V)./$(Bin)

build:
	$(V)$(CC) $(CCARGV) $(HEAD) -o $(Bin) $(Source)

dbuild:
	$(V)$(CC) $(CCARGV) $(HEAD) -o $(Bin) -g $(Source)

gdb: dbuild clean
	$(V)$(GDB) $(Bin)

externalCtags:
	$(V)$(CC) -M $(HEAD) $(Source) | sed -e 's/[\\ ]/\n/g' | sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | ctags -L - --c++-kinds=+p --fields=+iaS --extra=+q -f .rtags

clean:
	$(V)rm -rf $(Bin)
