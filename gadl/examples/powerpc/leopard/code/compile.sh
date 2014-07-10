#!/bin/sh
powerpc-elf-gcc testSerial.c -o testSerial.elf -g -Wl,-n,-Tinternal/script.ld,internal/crt0.o,-Map,testSerial.map -nostdlib
