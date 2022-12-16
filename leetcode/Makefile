V := @

Source := ./0084_largestRectangleArea.cpp
# Source := ./0000_test.cpp


CC := c++
# CC := clang++
VERSION := -std=c++14
ARGV := -W -Wall

RunAndClean: run clean

run: build
	$(V)./demo

build:
	$(V)$(CC) $(VERSION) $(ARGV) -o demo $(Source)

gdb:
	$(V)$(CC) $(VERSION) $(ARGV) -o demo -g $(Source)
	$(V)gdb -q ./demo -x ./tools/gdbinit
	$(V)rm -rf demo

clean:
	$(V)rm -rf demo
