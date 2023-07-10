CC := cc
C++ := c++
DBG := gdb

V := @

OUTPUT := runable

do-nothing:

cast:
	$(V)$(CC) cast.c -o $(OUTPUT)
	$(V)./$(OUTPUT)

cast-dbg:
	$(V)$(CC) cast.c -o $(OUTPUT) -g
	$(V)$(DBG) -q $(OUTPUT) -x init/cast-init

vtf-dbg:
	$(V)$(C++) vtable_function.cpp -o $(OUTPUT) -g
	$(V)$(DBG) -q $(OUTPUT) -x init/vtf-init

vtc-dbg:
	$(V)$(C++) vtable_class.cpp -o $(OUTPUT) -g
	$(V)$(DBG) -q $(OUTPUT) -x init/vtc-init

change-vt:
	$(V)$(C++) change_vtable.cpp -o $(OUTPUT) -g
	$(V)./$(OUTPUT)

clean:
	$(V)rm -rf $(OUTPUT)
