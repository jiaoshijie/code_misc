V := @

# Source := ./0098_is_valid_bst.rs
# Source := ./0000_test.rs

CC_Source := ./0025_reverseKGroup.cpp
# CC_Source := ./0000_test.cpp

CC := c++
# CC := clang++
CC_VERSION := -std=c++17
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
	$(V)$(CC) $(CC_VERSION) $(CC_ARGV) -o demo $(CC_Source)

cc-gdb:
	$(V)$(CC) $(VERSION) $(ARGV) -o demo -g $(CC_Source)
	$(V)gdb -q ./demo -x ./tools/gdbinit
	$(V)rm -rf demo

clean:
	$(V)rm -rf demo
