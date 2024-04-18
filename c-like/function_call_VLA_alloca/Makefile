V := @
CC := cc
ARGS := -g -no-pie
GDB := gdb

help:
	$(V)echo 'make [call|vla|ca|clean]'

call:
	$(V)$(CC) $(ARGS) call.c -o call
	$(V)$(GDB) -q ./call -x ./tools/gdb_call_init

vla:
	$(V)$(CC) $(ARGS) vla.c -o vla
	$(V)$(GDB) -q ./vla -x ./tools/gdb_vla_init

ca:
	$(V)$(CC) $(ARGS) ca.c -o ca
	$(V)$(GDB) -q ./ca -x ./tools/gdb_ca_init

clean:
	rm -rf call vla ca
