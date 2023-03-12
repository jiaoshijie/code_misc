V := @

Source := ./0086_partition.rs
# Source := ./0000_test.rs

CC := c++
# CC := clang++
CC_VERSION := -std=c++14
CC_ARGV := -W -Wall

rust: rust-run clean

rust-run: rust-build
	$(V)./demo

rust-build:
	$(V)rustc -o demo $(Source)

cc: cc-run clean

cc-run: cc-build
	$(V)./demo

cc-build:
	$(V)$(CC) $(CC_VERSION) $(CC_ARGV) -o demo $(Source)

cc-gdb:
	$(V)$(CC) $(VERSION) $(ARGV) -o demo -g $(Source)
	$(V)gdb -q ./demo -x ./tools/gdbinit
	$(V)rm -rf demo

clean:
	$(V)rm -rf demo
