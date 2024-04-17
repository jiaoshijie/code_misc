V := @
CC := cc
ARGS := -g -no-pie
GDB := gdb

call:
	$(V)$(CC) $(ARGS) call.c -o call
	$(V)$(GDB) -q ./call -x ./tools/gdb_call_init

clean:
	rm -rf call
