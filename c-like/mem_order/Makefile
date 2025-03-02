V := @
CC := cc
CFLAGS := -Wall -Wextra -O2
LIBS := -lpthread

help:
	@echo "e1"
	@echo "e2"

e1: e1.c
	$(V) $(CC) -o $@ $(CFLAGS) $(LIBS) $^

e2: e2.c
	$(V) $(CC) -o $@ $(CFLAGS) $(LIBS) $^

e3: e3.c
	$(V) $(CC) -o $@ $(CFLAGS) $(LIBS) $^

clean:
	rm e1 e2 e3
