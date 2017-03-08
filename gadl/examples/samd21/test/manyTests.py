#! /usr/bin/env python
# -*- coding: UTF-8 -*-

from __future__ import print_function
import sys, os
import subprocess
import argparse


def auto_int(x):    #used for argument parsing, it detects the base. It allows to use hexadecimal arguments.
    return int(x, 0)

if __name__ == '__main__':
    #arguments
    parser = argparse.ArgumentParser(description='Call many times the checker of Harmless disassembler against the objdump output. Cut address ranges into small parts.')
    parser.add_argument("-v", "--verbose",    
            help="be verbose…",
            action="store_true", default=False)
    parser.add_argument("-fr", "--fromRange",
            help="compare Harmless with objdump with opcodes range starting from FROMRANGE. Default 0",
            type=auto_int, default=0)
    parser.add_argument("-tr", "--toRange", 
            help="compare Harmless with objdump with opcodes range starting from TORANGE. Default to 0xdfff",
            type=auto_int, default=0xdfff)
    args = parser.parse_args()

    #chunk size:
    chunkSize = 128*1024    #128K instructions (~1s on my computer!)
    fr    = args.fromRange  #from range => not updated
    frUp  = args.fromRange  #from range updated for each step
    tr    = args.toRange    #to range => not updated
    trUp  = args.toRange    #to range updated for each step
    fullRange = tr-fr       #full range => not updated
    steps = fullRange/chunkSize + 1
    returnCode = False #i.e. no error
    #Ok. go
    while (frUp < tr) and not returnCode:
        trUp = min(tr,frUp+chunkSize)
        returnCode = subprocess.call(["./compileTest.py", "-fr", str(frUp) , "-tr", str(trUp)])
        if not returnCode:
            frUp = frUp + chunkSize
            if args.verbose:
                print('{val:3.1f}% of {size} steps\r'.format(val=min(100, float(frUp-fr) / fullRange * 100),size=steps),end='\r')
                sys.stdout.flush()
    if returnCode:
        print('FAILED: Try to run: ./compileTest.py -fr '+hex(frUp)+' -tr '+hex(trUp))

