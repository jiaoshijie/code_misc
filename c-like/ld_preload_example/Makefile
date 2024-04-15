# V := @

CC := cc
ARGS := -shared -fPIC

example: mymalloc
	$(V)LD_PRELOAD=./libmymalloc.so ls > /dev/null

example_count: mymallocount myfreecount
	$(V)LD_PRELOAD="./libmymallocount.so:./libmyfreecount.so" ls > /dev/null

mymalloc:
	$(V)$(CC) $(ARGS) ./mymalloc.c -o libmymalloc.so

mymallocount:
	$(V)$(CC) $(ARGS) ./mymallocount.c -o libmymallocount.so

myfreecount:
	$(V)$(CC) $(ARGS) ./myfreecount.c -o libmyfreecount.so

clean:
	rm -rf ./*.so
