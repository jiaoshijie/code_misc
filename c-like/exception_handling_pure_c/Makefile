# V := @
CC := cc
CFLAGS := -Wall -Wextra

BINS := example

all: $(BINS)

%: %.c
	$(V)$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BINS)
