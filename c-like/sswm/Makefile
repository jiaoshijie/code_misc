PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall -Wno-deprecated-declarations -Wno-unused-variable

build:
	@$(CC) $(CFLAGS) -I$(PREFIX)/include sswm.c -L$(PREFIX)/lib -lX11 -o sswm -g

env: build
	@env DISPLAY=:1 xwallpaper --zoom ~/.config/red_wallpaper
	@env DISPLAY=:1 ./sswm

vim-tags:
	@setctags_c sswm.c
	@cscope -Rbq

clean:
	rm -f sswm
