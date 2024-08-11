#!/usr/bin/env python3

import sys
import struct

index = 999;

def verify(num):
    global index

    if num == index:
        index += 1
    else:
        print(f"ERROR: {num} is not matched, which should be {index}")
        exit(1)

def to_int(str_bytes):
    if len(str_bytes) != 4:
        print("End of file")
        exit(0)

    return int.from_bytes(str_bytes, sys.byteorder)

def to_double(str_bytes):
    if len(str_bytes) != 8:
        print("End of file")
        exit(0)

    return struct.unpack('d', str_bytes)[0]

def main():
    fd = open("./log.file", "rb")

    fd.seek(1024, 0)
    while True:
        verify(to_int(fd.read(4)))

        fd.read(16)  # TODO: timespec

        verify(int(to_double(fd.read(8))))
        verify(int(to_double(fd.read(8))))
        verify(int(to_double(fd.read(8))))
        verify(int(to_double(fd.read(8))))

        verify(to_int(fd.read(4)))

    fd.close()


if __name__ == "__main__":
    main()
