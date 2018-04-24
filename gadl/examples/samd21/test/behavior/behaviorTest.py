#! /usr/bin/env python
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
#debugger = 'openocd' #either st-util or openocd
debugger = 'st-util' #either st-util or openocd

#verbose mode:
# - 0 => nothing, except for errors
# - 1 => default => one line for each test
# - 2 => more information (nb tests)
# - 3 => more information (json file)
# - 4 => information for each step.

regDict = {'r0':0, 'r1':1, 'r2':2, 'r3':3, 'r4':4, 'r5':5, 'r6':6, 'r7':7,
           'r8':8, 'r9':9,'r10':10, 'r11':11,'r12':12, 'sp':13,'lr':14, 'pc':15}
import types

def getInt(txt):
    # extract the integer type from a JSON txt
    # it can be either
    # - already an int
    # - a unicode string that represent:
    #   - an hexadecimal value (starting with '0x')
    #   - a decimal value
    if type(txt) is int:
        return txt
    else:
        try:
            if '0x' in txt:
                return int(txt,16)
            else:
                return int(txt,10)
        except Exception:
            print("error in integer conversion: "+txt)
            return 0

def debugStr(args, level, msg):
    if args.verbose > level:
        print(msg)

def getRegCombinationsForCode(inst,group,key):
    # for each reg, get the possible combinaisons
    # that may update the assembly code.
    if key in inst:
        sortedInstItemKeys = list(inst[key].keys())
        sortedInstItemKeys.sort()
        if key == 'codeData':
            #data structure for labels is not optimal
            #but it can be handled in the same way as register values
            #when calculating test combinations.
            labelId = 0
            case = []
            for access in sortedInstItemKeys: #either 'pre' or 'post'
                for data in inst[key][access]:
                    case.append({'label':'.Label'+str(labelId)})
                    labelId += 1
            if case:
                group.append({'label':case})
        else:
            for regName in sortedInstItemKeys:
                reg = inst[key][regName]
                case = []
                if 'idx' in reg:
                    for idxTxt in reg['idx']:
                        #idx = getInt(idxTxt)
                        case.append({'idx':idxTxt})
                if 'imm' in reg:
                    for immTxt in reg['imm']:
                        imm = getInt(immTxt)
                        case.append({'imm':imm})
                if case:
                    group.append({regName:case})
    return group

def getRegCombinationsForRuntime(inst,group,key):
    # for each reg, get the possible combinaisons
    # that do not depends on the assembly code.
    if key in inst:
        sortedRegKeys = list(inst[key].keys())
        sortedRegKeys.sort()
        for regName in sortedRegKeys:
            reg = inst[key][regName]
            case = []
            if 'val' in reg:
                for valTxt in reg['val']:
                    val = getInt(valTxt)
                    case.append({'val':val})
            if case:
                group.append({regName:case})
    return group

def debugComb(group,name):
    print(str(len(group))+' entries:')
    print(group)
    with open(name+".json", "w") as outfile:
        json.dump(group, outfile, indent=4)

#the 'forCode' boolean is used to determine if the combinations
#are used for the code generation, or the functionnal eval.
#in the first case, we do not need to give all combinations,
# (if we modify xPSR, the mnemonic is unchanged).
def combinations(inst, forCode):
    #first, get all cases for each register
    group = []
    for key in ['src', 'dest', 'codeData']:
        if forCode:
            getRegCombinationsForCode(inst,group,key)
            #debugComb(group, 'debugCode')
        else:
            getRegCombinationsForRuntime(inst,group,key)
            #debugComb(group, 'debugRuntime')

    #Then combine each register with the others
    keys = ['']*len(group) #we need an order
    index = {}  #the current index for each register
    size  = {}  #the maximum value
    cases = 1   #give the number of cases

    i = 0
    for entry in group: #list
        sortedEntryKeys = list(entry.keys())
        sortedEntryKeys.sort()
        for key in sortedEntryKeys: #only one...
            keys[i] = key
            nb = len(entry[key])
            size[key] = nb
            cases *= nb
            index[key] = 0
        i = i+1

    while True:
        result = {}
        #get one entry
        for entry in group: #group is a list
            sortedEntryKeys = list(entry.keys())
            sortedEntryKeys.sort()
            for key in sortedEntryKeys: #only one...
                result[key] = entry[key][index[key]]
        #send it
        yield result
        #compute the next
        i=0
        overflow = True
        while overflow and (i<len(group)):
            index[keys[i]] = index[keys[i]]+1
            overflow = (index[keys[i]] == size[keys[i]])
            if overflow:
                index[keys[i]] = 0
                i = i+1
        if i == len(group):
            return

def extractMnemo(inst, case):
    mnemo = inst['mnemo']
    #print(case)
    for reg in case:
        for idf in ('idx','imm','label'):
            if idf in case[reg]:
                mnemo = mnemo.replace('{'+reg+'}',str(case[reg][idf]))
    return mnemo

def getSourceFile(filename, inst):
    with open(filename+'.s',"w") as asm:
        labelId = 0
        asm.write(".text\n")
        asm.write(".syntax unified\n")
        asm.write(".thumb\n")
        #may have data in code before
        try:
            for data in inst['codeData']['pre']:
                asm.write('.Label'+str(labelId)+':\n')
                labelId += 1
                asm.write('\t.word '+str(getInt(data))+'\n') #convert -> int and str to check the data..
        except KeyError:
            pass #no key defined.
        asm.write(".global _start\n")
        asm.write("_start:\n")
        codeCases = []
        for case in combinations(inst,True):
            codeCases.append(case)
            asm.write('\t'+extractMnemo(inst,case)+'\n')
        asm.write("\tb .\n") #while(1);
        #may have data in code after
        try:
            for data in inst['codeData']['post']:
                asm.write('.Label'+str(labelId)+':\n')
                labelId += 1
                asm.write('\t.word '+str(getInt(data))+'\n')
        except KeyError:
            pass #no key defined.
        return codeCases

def compile(args,sourceFile):
    #asm
    debugStr(args,3,'compile file '+sourceFile+'.s')
    objFile = sourceFile+".o"
    try:
        returnCode = subprocess.call(["arm-none-eabi-as", "-mthumb", "-mcpu=cortex-m4", sourceFile+'.s', "-o", objFile])
    except OSError:
        print("The cross-compiler is not found (arm-none-eabi-gcc)")
        sys.exit(1)
    if returnCode != 0:
        print("*** Assembling, error " + str(returnCode) + " ***\n")
        print("see file "+sourceFile+'.s')
        sys.exit(returnCode)
    #link
    exeFile = sourceFile+".elf"
    debugStr(args,3,"link file to "+exeFile)
    returnCode = subprocess.call(["arm-none-eabi-ld", objFile, "-o", exeFile, "-Tinternal/script.ld"],)
    if returnCode != 0:
        print("*** Linking, error " + str(returnCode) + " ***\n")
        sys.exit(returnCode)
    return exeFile

def memCombinations(inst):
    """ memory combinations, from 'addr' and 'val' lists.
    - first cases, each addr has same value (-> len(val) cases)
    - second cases, rotation with values (->len(val) cases)
    """
    if 'mem' in inst:
        addrList = inst['mem']['addr']  #list of memory addresses
        valList = inst['mem']['val']    #list of different values
        #first: each memory have the same value
        for val in valList:
            valI = getInt(val)
            case = []
            for addr in addrList:
                case.append({'addr':getInt(addr), 'val':valI})
            yield case
        #then: rotation
        for indexStart in range(len(valList)):
            i = 0
            case = []
            for addr in addrList:
                case.append({'addr':getInt(addr), 'val':getInt(valList[(indexStart+i)%len(valList)])})
                i=i+1
            yield case

def getRuntimeTests(inst):
    runCases = []
    for caseR in combinations(inst,False):
        if 'mem' in inst:
            for caseM in memCombinations(inst):
                case = caseR.copy()
                case[u'mem'] = caseM
                runCases.append(case)
        else: #no 'mem' section
            runCases.append(caseR)
    return runCases

def prepareTestCaseForGdb(codeCase, runCase, gdb):
    sortedRunCasesKeys = list(runCase.keys())
    sortedRunCasesKeys.sort()
    for reg in sortedRunCasesKeys:
        if reg == 'mem': #this is not a reg…
            for memLocation in runCase[reg]:
                gdb.write('set {int}'+hex(memLocation['addr'])+' = '+str(memLocation['val'])+'\n')
        elif reg == "cpsr":
            if debugger == 'st-util':
                gdb.write('set $cpsr='+str(runCase[reg]['val'])+'\n')
            else:
                gdb.write('set $xPSR='+str(runCase[reg]['val'])+'\n')
        else:
            regName = str(codeCase[reg]['idx'])
            if regName != 'pc': #do not update pc, as it won't work.
                gdb.write('set $'+regName+'='+str(runCase[reg]['val'])+'\n')

def generateGdbScript(args, filename, inst, codeCases, runCases):
    if debugger != 'st-util' and debugger != 'openocd':
        print('error: no debugger specified : use st-link or openocd')
        print('assuming st-link')
        debugger == 'st-link'
    with open(filename+'.gdb',"w") as gdb:
        if debugger == 'st-util':
            gdb.write("tar extended-remote :4242\n")   #st-util
        else:# 'openocd'
            gdb.write("tar extended-remote :3333\n")    #openocd
            gdb.write("monitor reset halt\n")           #openocd
        gdb.write("set interactive-mode off\n")
        gdb.write("load\n")
        gdb.write("define dumpRegs\n")
        for i in range(13):
            gdb.write('\tprintf "0x%08x\\t",$r'+str(i)+'\n')
        gdb.write('\tprintf "0x%08x\\t",$sp\n')
        gdb.write('\tprintf "0x%08x\\t",$lr\n')
        gdb.write('\tprintf "0x%08x\\t",$pc\n')
        if debugger == 'st-util':
            gdb.write('\tprintf "0x%08x\\t",$cpsr\n')
        else:
            gdb.write('\tprintf "0x%08x\\t",$xPSR\n')
        if 'mem' in inst:
            for memAddr in inst['mem']['addr']:  #list of memory addresses
                gdb.write('\tprintf "0x%08x\\t",{int}'+memAddr+'\n')
        gdb.write('end\n\n')

        try:
            for reg in inst['init']:
                if reg in regDict:
                    gdb.write('set $'+reg+'='+str(inst['init'][reg])+'\n')
                else:
                    addr = getInt(reg)
                    val = inst['init'][reg]
                    gdb.write('set {int}'+hex(addr)+' = '+str(val)+'\n')
        except KeyError:
            pass

        gdb.write('set logging file '+filename+'_output.gdb\n')
        gdb.write('set logging redirect on\n')
        gdb.write('set logging on\n\n')

        testId = 0
        endTest = False
        for codeCase in codeCases: #list
            #first time
            if not endTest:
                gdb.write('set $oldpc = $pc\n')
            #prepare the case, with run time info
            for runCase in runCases: #list
                testId+=1
                #for early debug, only run 100 tests ('quick' CLI argument)
                endTest = args.quick and testId > 100
                if not(endTest) :
                    prepareTestCaseForGdb(codeCase, runCase, gdb)
                    gdb.write('dumpRegs()\n')
                    gdb.write('printf "A\\n"\n')
                    #then run the case
                    gdb.write('set logging off\n')
                    gdb.write('si\n')
                    gdb.write('set logging on\n')
                    #and get back register state.
                    gdb.write('dumpRegs()\n')
                    gdb.write('printf "B\\n"\n')
                    #svc?
                    gdb.write('if $pc==0x08000168\n')
                    gdb.write('\tset logging off\n')
                    gdb.write('\tsi\n')
                    gdb.write('\tset logging on\n')
                    gdb.write('\tdumpRegs()\n')
                    gdb.write('\tprintf "C\\n"\n')
                    gdb.write('end\n\n')
                    #always
                    gdb.write('set $pc = $oldpc\n')
            #pc is set before the current instruction
            #we have to point to the next instruction
            if not(endTest) :
                gdb.write('set $pc=$pc+'+str(inst['size'])+'\n\n')
        gdb.write('set logging off\n')
        gdb.write('quit\n')

import hashlib
def getJSONFileSignature(filename):
    with open(filename) as jsonFile:
        data=jsonFile.read().encode('utf-8')
        return hashlib.md5(data).hexdigest()

def readTargetOutputFile(filename):
    """ read the zipped output file
        and return either the list of lines
        or None if the file does not exists
    """
    targetOutputFile = filename+'_output.gdb.zip'
    try:
        root = zipfile.ZipFile(targetOutputFile)
        for name in root.namelist(): #only one name: filename+'_output.gdb'
            with root.open(name) as outputFile:
                return outputFile.readlines()
    except IOError:
        return None


def targetOutputFileToBuild(gdbOutputLines):
    """ This function checks that the target output file exists, and then
        - read the first line => that stores the md5 of the JSON file and the number of tests (and we have one test per line)
        - compare it with the JSON file of the test
        - if they differ, the test have been updated and the test should be done again.
    """
    sig = []
    jsonMd5 = getJSONFileSignature(filename)
    n = 0 #number of line in the file
    try:
        for line in gdbOutputLines:
            if n == 0: #signature in the first line
                sig = line.decode('utf-8').split()
            n += 1
        firstCond = jsonMd5 == sig[0] #md5 is ok
        #number of tests = 2 lines/test +preamble
        secondCond =  (n == int(sig[1])*2+2) or (n == int(sig[1])*3+2)  #3 lines if svc
        return not(firstCond and secondCond) , jsonMd5
    except TypeError: #gdbOutputLines is None
        return True, jsonMd5
    except IndexError:
        return True, jsonMd5
    except ValueError: #something, but error during parsing (int(…))
        return True, jsonMd5

def getStats(inst, codeCases, runCases):
    if args.verbose > 3:
        print("code to test instruction "+inst['instruction']+" requires:")
        print("\t"+str(len(codeCases))+" instructions in the code ("+str(len(codeCases)*inst['size'])+" bytes for the program)")
        print("\t"+str(len(runCases))+" tests for each instruction => "+str(len(codeCases)*len(runCases))+" cases")

#first line: md5 nbtests
#second line: list of registers (and memory locations).
def outputFilePreamble(outfile, signature, nbVal,inst):
    outfile.write(signature+'\t'+str(nbVal)+'\n')
    for i in range(len(regDict)):   #not optimized at all, but done only 2 times.
        for key in regDict:
            if i == regDict[key]:
                outfile.write("{reg:10s}\t".format(reg=key))
                break
    outfile.write('cpsr    \t')
    if 'mem' in inst:
        for memAddr in inst['mem']['addr']:  #list of memory addresses
            outfile.write("0x{mem:08x}\t".format(mem=getInt(memAddr)))
    outfile.write('\n')

import re
def bootCodeInFlash():
    #print('check boot\n')
    ### arm-none-eabi-gdb --eval-command="tar extended-remote :4242" --command=bootTest.gdb | grep bootKey
    remote=''
    if debugger == 'st-util':
        remote = 'tar extended-remote :4242'   #st-util
    else:# 'openocd'
        remote = 'tar extended-remote :3333'    #openocd
    try:
        process = subprocess.Popen(['arm-none-eabi-gdb','--eval-command='+remote, '--command=internal/bootTest.gdb'], stdout=subprocess.PIPE, bufsize=0)
    except OSError:
        print("The cross-debugger is not found (arm-none-eabi-gdb) -> cannot test on target. Exit…")
        sys.exit(1)
    process.wait()
    found = False
    p=re.compile('bootKey\s+([0-9a-fA-F]+)$')
    for line in process.stdout:
        m=p.match(line)
        if m:
            #print('boot line matching!')
            if m.groups()[0] == 'feeddeb0':
                found = True
            else:
                pass
                #print('wrong code: '+m.groups()[0])
    return found 

def processTestOnTarget(args, filename, inst, codeCases, runCases, signature, testStr, bootCodeChecked):
    testOnTargetOk = False
    nbVal = len(codeCases)*len(runCases)
    #we have to do the test
    debugStr(args,3,'tests on target should be done')
    if args.target:
        #0- check that the code in ROM is Ok.
        if not bootCodeChecked:
            if not bootCodeInFlash():
                print('boot code not in flash')
                print(' -> run make in dir internal/')
                print(' -> then flash the target with internal/boot.elf')
                print(' -> and re-run the test suite')
                sys.exit(1)
        #1- generate the gdb script
        generateGdbScript(args, filename, inst, codeCases, runCases)
        #2- create the output file (starting with md5)
        outputFile = filename+'_output.gdb'
        with open(outputFile, "w") as outfile:
            outputFilePreamble(outfile, signature, nbVal,inst)
        #3- run the test on target
        #arm-none-eabi-gdb beh_lsl.json.elf -q -x beh_lsl.json.gdb
        debugStr(args,3,'run test on target…')
        try:
            process = subprocess.Popen(['arm-none-eabi-gdb','-q', filename+'.elf','-x',filename+'.gdb'], stdout=subprocess.PIPE, bufsize=0)
        except OSError:
            print("The cross-debugger is not found (arm-none-eabi-gdb) -> cannot test on target. Exit…")
            sys.exit(1)
        if args.verbose > 0:
            gdbWaitVal = 0
            print('', end='\r')
            for line in process.stdout:
                print(testStr+' {val:3.1f}%'.format(val=min(100, float(gdbWaitVal) / nbVal * 100)), end='\r')
                gdbWaitVal = gdbWaitVal + 1
        process.wait()
        print(testStr, end = '')
        debugStr(args,3,'\ndone!\n')
        testOnTargetOk = True
        #4- zip the generated file
        if os.path.isfile(outputFile):
            zf = zipfile.ZipFile(outputFile+'.zip',mode='w')
            zf.write(outputFile, compress_type=zipfile.ZIP_DEFLATED)
            zf.close()
    else:
        debugStr(args,3,"test on target cancelled (no command line option)")
    return testOnTargetOk

def harmlessPrintReg(inst,core,out):
    for id in range(16):
        out.write("0x{reg:08x}\t".format(reg=core.gpr_read32(id)))
    out.write("0x{reg:08x}\t".format(reg=core.CPSR()))
    if 'mem' in inst:
        for memAddr in inst['mem']['addr']:  #list of memory addresses
            out.write("0x{mem:08x}\t".format(mem=core.mem_read32(getInt(memAddr))))

def harmlessInit(regDict, core,filename):
    #init regs
    for id in range(16):
        core.gpr_write32(id,0)
    core.setCPSR(0x01000000) # Thumb bit in cpsr required!
    core.setITSTATE(0)
    #load program
    core.readCodeFile("internal/boot.elf") #code for vectors (in flash)
    core.readCodeFile(filename+".elf")
    #set init sequence
    try:
        for reg in inst['init']:
            if reg in regDict:
                core.gpr_write32(regDict[reg], getInt(inst['init'][reg]))
            else: #memory?
                addr = getInt(reg)
                val = getInt(inst['init'][reg])
                #print('address '+str(addr)+', val:'+str(val))
                core.mem_write32(addr,val)
    except KeyError:
        pass #no 'init' section in JSON file, skip

def processTestOnHarmless(args, filename, inst, codeCases, runCases, signature):
    sys.path.append("../../samd21")
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
    harmlessInit(regDict, core, filename)
    with open(harmlessFile,'w') as out:
        nbVal = len(codeCases)*len(runCases)
        outputFilePreamble(out, signature, nbVal,inst)
        testId = 0
        for codeCase in codeCases: #list
            oldPC = core.programCounter()
            for runCase in runCases: #list
                testId+=1
                #for early debug, only run 100 tests ('quick' CLI argument)
                endTest = args.quick and testId > 100
                if not endTest:
                    #init
                    sortedRunCasesKeys = list(runCase.keys())
                    sortedRunCasesKeys.sort()
                    for reg in sortedRunCasesKeys:
                        if reg == 'mem': #this is not a reg…
                            for memLocation in runCase[reg]:
                                #print('maj mem '+hex(memLocation['addr'])+' -> '+hex(memLocation['val']))
                                core.mem_write32(memLocation['addr'],memLocation['val'])
                        elif reg == "cpsr":
                            core.setCPSR(getInt(runCase[reg]['val']))
                        else:
                            regName = codeCase[reg]['idx']
                            if regName != 'pc': #do not update pc, as it won't work.
                                core.gpr_write32(regDict[codeCase[reg]['idx']], getInt(runCase[reg]['val']))
                                #print('reg '+str(regDict[codeCase[reg]['idx']])+' -> 0x{val:08x}'.format(val=getInt(runCase[reg]['val'])))
                    #print('---')
                    #exec one instruction
                    harmlessPrintReg(inst,core,out)
                    out.write('A\n')
                    #print('before instruction : '+core.disassemble(core.gpr_read32(15),1,True))
                    core.execInst(1)
                    #print registers
                    harmlessPrintReg(inst,core,out)
                    out.write('B\n')
                    #special case for svc… 2 instructions
                    if core.gpr_read32(15) == 0x08000168:
                        core.execInst(1)
                        harmlessPrintReg(inst,core,out)
                        out.write('C\n')
                    #get back…
                    core.setProgramCounter(oldPC)
            core.setProgramCounter(core.programCounter()+getInt(inst['size']))
import zipfile

def clean(filename, gdbOutputLines, result):
    #remove uneeded files
    exts = ['.gdb', '.o', '.s']
    if result != 1:
        exts.append('_output.harmless')
        exts.append('_output.gdb')
        exts.append('.elf')
    else: #there was a pb… restore output gdb file.
        if not os.path.isfile(filename+'_output.gdb'):
            with open(filename+'_output.gdb', "w") as outfile:
                for line in gdbOutputLines:
                    outfile.write(str(line.decode('utf-8')))
    for ext in exts:
        try:
            os.remove(filename+ext)
        except OSError:
            pass

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

def getCurrentTestString(args, inst, instructionIndex, filename, nbVal):
    s = max(0,25-len(inst['instruction']))
    result = '[{0:3d}'.format(instructionIndex+1)
    if args.verbose > 2:
        result += ' - {filen:30}'.format(filen=filename)
    if args.verbose > 1:
        result += ' - {case:5} cases'.format(case=nbVal)
    result += '] check instruction: '+inst['instruction']+s*' '+'-> '
    return result

def compare(testOnTargetOk, filename, gdbOutputLines, testStr):
    ok = 0
    if testOnTargetOk:
        try:
            with open(filename+'_output.harmless') as harmless:
                for line in zip(gdbOutputLines, harmless): #line[0] gdb, line[1] harmless
                    if line[0].decode('utf-8') != line[1]:
                        ok = 1
        except IOError:
            ok = 2
    else:
        ok = 2
    #report (string already printed if verbose > 0. Print only if pb)
    if ((args.verbose == 0) and (ok != 0)):
        print(testStr, end='')
    if (args.verbose > 0) and (ok == 0):
        print(BOLD()+GREEN()+'ok'+ENDC())
    if ok != 0:
        if ok == 1:
            print(BOLD()+RED()+'failed'+ENDC()+'\t(file '+filename+')')
            if args.verbose > 1:
                print('comparison: gvimdiff '+filename+'_output.gdb '+filename+'_output.harmless')
                print('asm       : arm-none-eabi-objdump -d '+filename+'.elf')
        elif ok == 2:
            print(BOLD()+YELLOW()+'impossible (no target file)'+ENDC())
    return ok

def debugRuntimeTests(runCases):
    nb=0
    for runCase in runCases: #list
        print(str(nb), end='\t')
        sortedRunCasesKeys = list(runCase.keys())
        sortedRunCasesKeys.sort()
        for reg in sortedRunCasesKeys:
            if reg == 'mem': #this is not a reg…
                for memLocation in runCase[reg]:
                    print('mem '+hex(memLocation['addr'])+' -> '+hex(memLocation['val']),end='\t')
            elif reg == "cpsr":
                print('cpsr:'+str(getInt(runCase[reg]['val'])),end='\t')
            else:
                print('reg 0x{reg:08x}'.format(reg=getInt(runCase[reg]['val'])),end='\t')
        print()
        nb += 1

import json
if __name__ == '__main__':
    #arguments
    parser = argparse.ArgumentParser(description='Check Harmless Cortex ARM model functionnal behavior against a real target')
    parser.add_argument("-nc", "--noclean",
            help="do not remove intermediate files (asm, .elf, …)",
            action="store_true", default=False)
    parser.add_argument("-s", "--assembleOnly",
            help="only generate the assembly test file",
            action="store_true", default=False)
    parser.add_argument('-v','--verbose', const=1, default=1, type=int,
              help='The verbose level 0 to 3 (higher => more debug information), default 1', nargs='?')
    parser.add_argument("-q", "--quick",
            help="short test on only 100 test cases for early debug",
            action="store_true", default=False)
    parser.add_argument("-t", "--target",
            help="run test on target (if required)",
            action="store_true", default=False)
    parser.add_argument('files', metavar='file', nargs='+',
                    help='JSON instruction test spec')
    args = parser.parse_args()

    timeStart = time.clock()
    #0 - read the JSON instruction test
    nbTests = 0
    nbInstructions = 0
    bootCodeChecked = False
    for filename in args.files:
        with open(filename) as jsonFile:
            inst = json.load(jsonFile)
        #1- generate the object file for Harmless and real target from the JSON test
        codeCases = getSourceFile(filename,inst)
        #2- compile it
        exeFile= compile(args,filename)
        if not args.assembleOnly:
            #3- get tests for runtime
            runCases = getRuntimeTests(inst)
            #debugRuntimeTests(runCases)
            ##4- stats (if verbose mode > 2)
            nbVal = len(codeCases)*len(runCases)
            nbTests += nbVal
            getStats(inst, codeCases, runCases)
            #4.5- print the instruction string
            if (args.verbose > 0):
                testStr = getCurrentTestString(args, inst, nbInstructions, filename, nbVal)
                print(testStr, end='')
            #5- run tests on the real target (if needed)
            testOnTargetOk = False
            gdbOutputLines = readTargetOutputFile(filename)
            shouldBuild, signature = targetOutputFileToBuild(gdbOutputLines) #check with md5
            if shouldBuild:
                testOnTargetOk = processTestOnTarget(args, filename, inst, codeCases, runCases, signature, testStr, bootCodeChecked)
                bootCodeChecked = True #check boot code only once.
                #read the output file (maybe again…)
                gdbOutputLines = readTargetOutputFile(filename)
            else:
                testOnTargetOk = True
                debugStr(args,3,'tests on target up to date')
            #6- run tests on Harmless
            if testOnTargetOk:
                processTestOnHarmless(args, filename, inst, codeCases, runCases, signature)
                #print('test on harmless…')
            #7- compare
            result = compare(testOnTargetOk, filename, gdbOutputLines, testStr)

            #8- clean (remove tmp files)
            if not args.noclean:
                clean(filename, gdbOutputLines, result)
            nbInstructions += 1
        else: # assembly only
            subprocess.call(["arm-none-eabi-objdump", "-d", filename+'.elf'],)
    debugStr(args,0,str(nbTests)+' tests done for '+str(nbInstructions)+' instructions in {t:.2f}s\n'.format(t=(time.clock()-timeStart)))

