#!/usr/bin/env python3

import sys
import struct

def main():
    fd = open("./log.file", "rb")

    fd.seek(1024, 0)

    while True:
        id = fd.read(4)

        fd.read(16)  # TODO: timespec

        pos = fd.read(8)
        vel = fd.read(8)
        pos_cmd = fd.read(8)
        vel_cmd = fd.read(8)
        cpos = fd.read(4)

        print(int.from_bytes(id, sys.byteorder),
            struct.unpack('d', pos)[0],
            struct.unpack('d', vel)[0],
            struct.unpack('d', pos_cmd)[0],
            struct.unpack('d', vel_cmd)[0],
            int.from_bytes(cpos, sys.byteorder),
            )

    fd.close()


if __name__ == "__main__":
    main()
