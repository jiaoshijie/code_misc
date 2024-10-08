#!/usr/bin/env python3

import sys
import struct

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
        id = to_int(fd.read(4))

        fd.read(16)  # TODO: timespec

        pos = to_double(fd.read(8))
        vel = to_double(fd.read(8))
        pos_cmd = to_double(fd.read(8))
        vel_cmd = to_double(fd.read(8))
        cpos = to_int(fd.read(4))

        print(id, pos, vel, pos_cmd, vel_cmd, cpos)

    fd.close()


if __name__ == "__main__":
    main()
