#!/usr/bin/env bash

set -xe

SOURCES="main.c fp.c"

DEBUG="-g"

CC="cc"
CFLAGS="-Wall -Wextra"
BINARY="fp"

${CC} -o ${BINARY} ${DEBUG} ${SOURCES} ${CFLAGS}
