all: httpd

httpd: httpd.c
	gcc -W -Wall -lpthread -o httpd httpd.c

debug: httpd.c
	gcc -W -Wall -lpthread -o httpd httpd.c -g

clean:
	rm httpd
