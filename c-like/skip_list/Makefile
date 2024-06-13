V := @

CC := cc
ARGS := -Wall -Wextra -Werror
BIN := demo

SRC := skip_list.c test.c

run: build
	$(V)./$(BIN)

build:
	$(V)$(CC) $(ARGS) $(SRC) -o $(BIN)
