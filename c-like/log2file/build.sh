#!/usr/bin/env bash

set -xe

CC=cc

SRC_FILES="main.c cJSON.c"
CFLAGS="-Wall -Wextra -O2"
BINARY="log"


DEBUG=""

while [[ $# -gt 0 ]]; do
  case $1 in
    -g)
      DEBUG="-g"
      shift
      ;;
    *)
      echo -e "\e[31mERROR\e[0m: Unsupported Argument!!!"
      shift
      exit 1
      ;;
  esac
done

rm -rf ./log.file

${CC} -o ${BINARY} ${CFLAGS} ${SRC_FILES} ${DEBUG}
