#! /usr/bin/env python
# -*- coding: UTF-8 -*-

from __future__ import print_function
from multiprocessing import Pool, cpu_count
import sys, os
import subprocess
import argparse

#rpocesses run in parallel
def runProcess(params):
    addrFrom = params[0]
    addrTo = params[1]
    num = params[2]
    returnCode = subprocess.call(["./compileTest.py", "-fr", str(addrFrom) , "-tr", str(addrTo), "-b", "build"+str(num), "-c"])
    return returnCode

def auto_int(x):    #used for argument parsing, it detects the base. It allows to use hexadecimal arguments.
    return int(x, 0)

if __name__ == '__main__':
    #chunk size:
    chunkSize = 128*1024    #128K instructions (~1s on my computer!)
    #arguments
    parser = argparse.ArgumentParser(description='Call many times the checker of Harmless disassembler against the objdump output (compileTest.py). Cut address ranges into small parts of '+str(chunkSize)+' instructions')
    parser.add_argument("-v", "--verbose",    
            help="be verbose…",
            action="store_true", default=False)
    parser.add_argument("-fr", "--fromRange",
            help="compare Harmless with objdump with opcodes range starting from FROMRANGE. Default 0",
            type=auto_int, default=0)
    parser.add_argument("-tr", "--toRange", 
            help="compare Harmless with objdump with opcodes range starting from TORANGE. Default to 0xdfff",
            type=auto_int, default=0xdfff)
    parser.add_argument("-j", "--jobs", 
            help="use multiprocessing to dispatch jobs in parallel. Default to the number of cores of the host.",
            type=int, default=cpu_count())
    args = parser.parse_args()

    fr    = args.fromRange  #from range => not updated
    tr    = args.toRange    #to range => not updated
    fullRange = tr-fr       #full range => not updated
    if fullRange < 0:
        print('invalid range: toRange parameter should be greater than fromRange')
        sys.exit(1)
    steps = int(fullRange/chunkSize) + 1
    if args.verbose:
        print('dispatch '+str(steps)+' steps on '+str(args.jobs)+' parallel jobs ('+str(fullRange)+' instructions to compare)')
    nbStepsDone = 0    #incremented at the end of process
    stepsParam = []

    #create args for process pool.
    for i in range(steps):
        frUp = fr + i*chunkSize
        trUp = min(frUp+chunkSize,tr)
        stepsParam.append((frUp,trUp,i)) #from, to, number

    #start pool (python 2.x style...)
    pool = Pool(processes=args.jobs)
    errorFound = False
    for result in pool.imap(runProcess, stepsParam):
        if result != 0:
            pool.terminate()
            errorFound = True
            break
        nbStepsDone = nbStepsDone + 1
        if args.verbose:
            print('\r{val:3.1f}% ({done}) of {size} steps'.format(val=min(100, float(nbStepsDone) / steps * 100),
                done=nbStepsDone, size=steps),end='')
            sys.stdout.flush()
    print()
    if errorFound:
        print("FAILED")
        sys.exit(1)
    
