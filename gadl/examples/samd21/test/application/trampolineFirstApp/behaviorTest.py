#! /usr/bin/env python3
# -*- coding: UTF-8 -*-

from __future__ import print_function
import sys, os
import subprocess
import argparse
import shutil
import time

# test sur cible avec openocd ou st-util
# -> voir  generateGdbScript
# avec openocd, il faut lancer le serveur: openocd -f board/st_nucleo_f3.cfg
# avec jlink: JLinkGDBServer -device ATSAMD21J18 -if SWD -speed 4000 -autoconnect 1 
#             Warning: tests available only on st Nucleo F303 (Memory mapping…)
#debugger = 'openocd' #either st-util, openocd or jlink
#debugger = 'jlink'
debugger = 'st-util' 

#verbose mode:
# - 0 => nothing, except for errors
# - 1 => default => one line for each test
# - 2 => more information (nb tests)
# - 3 => more information (json file)
# - 4 => information for each step.

regDict = {'r0':0, 'r1':1, 'r2':2, 'r3':3, 'r4':4, 'r5':5, 'r6':6, 'r7':7,
           'r8':8, 'r9':9,'r10':10, 'r11':11,'r12':12, 'sp':13,'lr':14, 'pc':15}
import types

def generateGdbScript(filename, nb):
    global debugger
    debugPort = {'st-util':4242,'openocd':3333,'jlink':2331}
    debugPSR  = {'st-util':'cpsr','openocd':'xPSR','jlink':'xpsr'}
    if debugger not in ['st-util', 'openocd', 'jlink']:
        print('error: no debugger specified : use st-link, openocd or jlink')
        print('assuming st-link')
        debugger = 'st-link'
    with open(filename+'.gdb',"w") as gdb:
        gdb.write("file {filen}.elf\n".format(filen=filename))
        gdb.write("tar extended-remote :{port}\n".format(port=debugPort[debugger]))
        if debugger == 'openocd':
            gdb.write("monitor reset halt\n")           #openocd
        gdb.write("set interactive-mode off\n")
        #gdb.write("load\n")
        gdb.write("define dumpRegs\n")
        for i in range(13):
            gdb.write('\tprintf "0x%08x\\t",$r'+str(i)+'\n')
        gdb.write('\tprintf "0x%08x\\t",$sp\n')
        gdb.write('\tprintf "0x%08x\\t",$lr\n')
        gdb.write('\tprintf "0x%08x\\t",$pc\n')
        gdb.write('\tprintf "0x%08x\\t",${psr}\n'.format(psr=debugPSR[debugger]))
        gdb.write('end\n\n')

        gdb.write('set logging file '+filename+'_output.gdb\n')
        gdb.write('set logging redirect on\n')

        testId = 0
        endTest = False
        gdb.write('set $i = 0\n')
        gdb.write('while($i<{n})\n'.format(n=nb))
        gdb.write('\tset $i = $i + 1\n')
        gdb.write('\tset logging on\n')
        gdb.write('\tdumpRegs()\n')
        gdb.write('\tprintf "A\\n"\n')
        gdb.write('\tset logging off\n')
        #then run the case
        gdb.write('\tsi\n')
        gdb.write('end\n')
        gdb.write('quit\n')


def processTestOnTarget(filename,nb):
    #1- generate the gdb script
    generateGdbScript(filename,nb)
    #2- run the test on target
    #arm-none-eabi-gdb beh_lsl.json.elf -q -x beh_lsl.json.gdb
    try:
        process = subprocess.Popen(['arm-none-eabi-gdb','-q', filename+'.elf','-x',filename+'.gdb'], stdout=subprocess.PIPE, bufsize=0)
    except OSError:
        print("The cross-debugger is not found (arm-none-eabi-gdb) -> cannot test on target. Exit…")
        sys.exit(1)
    process.wait()

def harmlessPrintReg(core,out):
    for id in range(16):
        out.write("0x{reg:08x}\t".format(reg=core.gpr_read32(id)))
    out.write("0x{reg:08x}\t".format(reg=core.CPSR()))

def harmlessInit(core,filename):
    #init regs
    for id in range(16):
        core.gpr_write32(id,0)
    core.gpr_write32(13,0x20003000)
    core.gpr_write32(14,0xffffffff)
    core.setCPSR(0x01000000) # Thumb bit in cpsr required!
    core.setITSTATE(0)
    #load program
    core.readCodeFile(filename+".elf")

def processTestOnHarmless(filename,nb):
    sys.path.append("../../../samd21")
    harmlessFile = filename+"_output.harmless"
    try:
        import samd21
    except ImportError:
        print("simulator lib not generated")
        print("first run gadl:")
        print("$gadl ./samd21.cpu")
        print("Then go to the new samd21/ dir and build the python lib")
        print("$cd samd21")
        print("$make python")
        sys.exit()
    sam = samd21.cpu()
    core = sam.core0()
    harmlessFile = filename+"_output.harmless"
    harmlessInit(core, filename)
    with open(harmlessFile,'w') as out:
        for inst in range(nb):
            harmlessPrintReg(core,out)
            out.write('A\n')
            #print('before instruction : '+core.disassemble(core.gpr_read32(15),1,True))
            core.execInst(1)
    
import zipfile

def BLACK () :
  return '\033[90m'

def RED () :
  return '\033[91m'

def GREEN () :
  return '\033[92m'

def YELLOW () :
  return '\033[93m'

def BOLD () :
  return '\033[1m'

def ENDC () :
  return '\033[0m'

def compare(filename):
    ok = 0
    try:
        with open(filename+'_output.harmless') as harmless:
            with open(filename+'_output.gdb')  as gdb:
                for line in zip(gdb, harmless): #line[0] gdb, line[1] harmless
                    if line[0].decode('utf-8') != line[1]:
                        ok = 1
    except IOError:
        ok = 2
    #report (string already printed if verbose > 0. Print only if pb)
    if (ok == 0):
        print(BOLD()+GREEN()+'ok'+ENDC())
    else:
        if ok == 1:
            print(BOLD()+RED()+'failed'+ENDC()+'\t(file '+filename+')')
            print('comparison: gvimdiff '+filename+'_output.gdb '+filename+'_output.harmless')
            print('asm       : arm-none-eabi-objdump -d '+filename+'.elf')
        elif ok == 2:
            print(BOLD()+YELLOW()+'impossible (no comparison file)'+ENDC())
    return ok

if __name__ == '__main__':
    filename = 'appli_IF'
    nbInst = 20000
    #arguments
    #processTestOnTarget(filename,nbInst)
    processTestOnHarmless(filename,nbInst)
    result = compare(filename)

