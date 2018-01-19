#! /usr/bin/env python
# -*- coding: UTF-8 -*-

from __future__ import print_function
import sys, os
import subprocess
import argparse
import shutil
import time

# d'abord on crée un fichier avec les instructions à tester:
#Exemple pour lsl: lsl Rd, Rm, #imm5
# => toutes les valeurs de Rd, Rm, imm5 ? => soit 2048 instructions.
# il faut une taille contenue, car flashage sur vraie carte.
# c'est fait une seule fois.

#ensuite, on va faire une execution sur la cible
#on flashe
# on donne des pattern pour les registres utilisés: Rm, imm5
# ici, Rm: 10 valeurs au hasard, ainsi que 0, ffffffff, 0xaaaaaaaa, 0x55555555, 0x12345678, 0xfedcba98
# => les valeurs au hasard doivent être memorisées, car on fait le test sur la flash une seule fois.
# de même pour le imm5
# valeur de APSR au début, 3 bits
# en tout: 8 (APSR) * 8 (Rm) * 32 (imm5) *2048 instructions => 4M tests. C'est trop

#en sortie, on stocke l'état des variables de sortie: Rd, APSR.

#definition directement avec des structures Python? => plus simple. Ou du JSON?
# lsl{
#     src:
#        reg Rm {idx: {0,2,7}, val = {0, ffffffff, 0xaaaaaaaa…}}
#        imm imm5 {val = {…}}
#     dst:
#        APSR --connu => tout à 0, et tout à 1 si sortie uniquement.
#        Rd {idx = {0, 2, 7}
#     mnemo "lsls Rd, Rm, #imm5" -- pour générer le code
# }

# test sur cible avec openocd ou st-util
# -> voir  generateGdbScript
# avec openocd, il faut lancer le serveur: openocd -f board/st_nucleo_f3.cfg

#verbose mode:
# - 0 => nothing, except for errors
# - 1 => default => one line for each test
# - 2 => more information (json file)
# - 3 => information for each step.

import types

def getInt(txt):
    # extract the integer type from a JSON txt
    # it can be either
    # - already an int
    # - a unicode string that represent:
    #   - an hexadecimal value (starting with '0x')
    #   - a decimal value
    if type(txt) is types.IntType:
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

def getRegCombinationsForCode(inst,group,key):
    # for each reg, get the possible combinaisons
    # that may update the assembly code.
    if key in inst:
        if key == 'codeData':
            #data structure for labels is not optimal
            #but it can be handled in the same way as register values
            #when calculating test combinations.
            labelId = 0
            case = []
            for access in inst[key]: #either 'pre' or 'post'
                for data in inst[key][access]:
                    case.append({'label':'.Label'+str(labelId)})
                    labelId += 1
            if case:
                group.append({'label':case})
        else:
            for regName in inst[key]:
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
        for regName in inst[key]:
            reg = inst[key][regName]
            case = []
            if 'val' in reg:
                for valTxt in reg['val']:
                    val = getInt(valTxt)
                    case.append({'val':val})
            if case:
                group.append({regName:case})
    return group

def debug(group,name):
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
            #debug(group, 'debugCode')
        else:
            getRegCombinationsForRuntime(inst,group,key)
            #debug(group, 'debugRuntime')

    #Then combine each register with the others

    keys = ['']*len(group) #we need an order
    index = {}  #the current index for each register
    size  = {}  #the maximum value
    cases = 1   #give the number of cases

    i = 0
    for entry in group:
        for key in entry: #only one...
            keys[i] = key
            nb = len(entry[key])
            size[key] = nb
            cases *= nb
            index[key] = 0
        i = i+1

    while True:
        result = {}
        #get one entry
        for entry in group:
            for key in entry: #only one...
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
    if args.verbose > 2:
        print("compile file "+sourceFile+'.s')
    objFile = sourceFile+".o"
    try:
        returnCode = subprocess.call(["arm-none-eabi-as", "-mthumb", "-mcpu=cortex-m4", sourceFile+'.s', "-o", objFile])
    except OSError:
        print("The cross-compiler is not found (arm-none-eabi-gcc)")
        sys.exit(1)
    if returnCode != 0:
        print("*** Assembling, error " + str(returnCode) + " ***\n")
        sys.exit(returnCode)
    #link
    exeFile = sourceFile+".elf"
    if args.verbose > 2:
        print("link file to "+exeFile)
    returnCode = subprocess.call(["arm-none-eabi-ld", objFile, "-o", exeFile, "-Tscript.ld"],)
    if returnCode != 0:
        print("*** Linking, error " + str(returnCode) + " ***\n")
        sys.exit(returnCode)
    return exeFile

def getRuntimeTests(inst):
    runCases = []
    for case in combinations(inst,False):
        runCases.append(case)
    return runCases

def prepareTestCaseForGdb(codeCase, runCase, gdb):
    for reg in runCase:
        if reg == "cpsr":
            #gdb.write('set $cpsr='+str(runCase[reg]['val'])+'\n')
            gdb.write('set $xPSR='+str(runCase[reg]['val'])+'\n')
        else:
            regName = str(codeCase[reg]['idx'])
            if regName != 'pc': #do not update pc, as it won't work.
                gdb.write('set $'+regName+'='+str(runCase[reg]['val'])+'\n')

def generateGdbScript(filename, inst, codeCases, runCases):
    with open(filename+'.gdb',"w") as gdb:
        #gdb.write("tar extended-remote :4242\n")   #st-util
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
        #gdb.write('\tprintf "0x%08x\\t",$cpsr\n')
        gdb.write('\tprintf "0x%08x\\t",$xPSR\n')
        gdb.write('end\n\n')

        try:
            for reg in inst['init']:
                gdb.write('set $'+reg+'='+str(inst['init'][reg])+'\n')
        except KeyError:
            pass

        gdb.write('set logging file '+filename+'_output.gdb\n')
        gdb.write('set logging redirect on\n')
        gdb.write('set logging on\n\n')

        for codeCase in codeCases:
            #first time
            gdb.write('set $oldpc = $pc\n')
            #prepare the case, with run time info
            for runCase in runCases:
                prepareTestCaseForGdb(codeCase, runCase, gdb)
                gdb.write('dumpRegs()\n')
                gdb.write('printf "A\\n"\n')
                #then run the case
                gdb.write('set logging off\n')
                gdb.write('si\n')
                gdb.write('set logging on\n')
                #and get back register state.
                gdb.write('dumpRegs()\n')
                gdb.write('printf "B\\n"\n\n')
                #always
                gdb.write('set $pc = $oldpc\n')
            #pc is set before the current instruction
            #we have to point to the next instruction
            gdb.write('set $pc=$pc+'+str(inst['size'])+'\n\n')
        gdb.write('set logging off\n')
        gdb.write('quit\n')

import hashlib
def getJSONFileSignature(filename):
    with open(filename) as jsonFile:
        data=jsonFile.read()
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
                sig = line.split()
            n += 1
        firstCond = jsonMd5 == sig[0] #md5 is ok
        secondCond =  n == int(sig[1])*2+1 #number of tests = 2 lines/test +signature line)
        return not(firstCond and secondCond) , jsonMd5
    except TypeError: #gdbOutputLines is None
        return True, jsonMd5
    except IndexError:
        return True, jsonMd5
    except ValueError: #something, but error during parsing (int(…))
        return True, jsonMd5

def getStats(inst, codeCases, runCases):
    if args.verbose > 2:
        print("code to test instruction "+inst['instruction']+" requires:")
        print("\t"+str(len(codeCases))+" instructions in the code ("+str(len(codeCases)*inst['size'])+" bytes for the program)")
        print("\t"+str(len(runCases))+" tests for each instruction => "+str(len(codeCases)*len(runCases))+" cases")

def processTestOnTarget(args, filename, inst, codeCases, runCases, signature):
    testOnTargetOk = False
    nbVal = len(codeCases)*len(runCases)
    #we have to do the test
    if args.verbose > 2:
        print('tests on target should be done')
    if args.target:
        #1- generate the gdb script
        generateGdbScript(filename, inst, codeCases, runCases)
        #2- create the output file (starting with md5)
        outputFile = filename+'_output.gdb'
        with open(outputFile, "w") as outfile:
            outfile.write(signature+' '+str(nbVal)+'\n')
        #3- run the test on target
        #arm-none-eabi-gdb beh_lsl.json.elf -q -x beh_lsl.json.gdb
        if args.verbose > 2:
            print('run test on target…')
        try:
            process = subprocess.Popen(['arm-none-eabi-gdb','-q', filename+'.elf','-x',filename+'.gdb'], stdout=subprocess.PIPE, bufsize=0)
        except OSError:
            print("The cross-debugger is not found (arm-none-eabi-gdb) -> cannot test on target. Exitting…")
            sys.exit(1)
        if args.verbose > 0:
            gdbWaitVal = 0
            for line in process.stdout:
                print('--> {val:3.1f}%'.format(val=min(100, float(gdbWaitVal) / nbVal * 100)), end='\r')
                gdbWaitVal = gdbWaitVal + 1
        process.wait()
        if args.verbose > 2:
            print('\ndone!\n')
        testOnTargetOk = True
        #4- zip the generated file
        if os.path.isfile(outputFile):
            zf = zipfile.ZipFile(outputFile+'.zip',mode='w')
            zf.write(outputFile, compress_type=zipfile.ZIP_DEFLATED)
            zf.close()
    else:
        if args.verbose > 2:
            print("test on target cancelled (no command line option)")
    return testOnTargetOk

def harmlessPrintReg(core,out):
    for id in range(16):
        out.write("0x{reg:08x}\t".format(reg=core.gpr_read32(id)))
    out.write("0x{reg:08x}\t".format(reg=core.CPSR()))

def harmlessInit(regDict, core,filename):
    #init regs
    for id in range(16):
        core.gpr_write32(id,0)
    core.setCPSR(0x01000000) # Thumb bit in cpsr required!
    core.setITSTATE(0)
    #load program
    core.readCodeFile(filename+".elf")
    #set init sequence
    try:
        for reg in inst['init']:
            core.gpr_write32(regDict[reg], getInt(inst['init'][reg]))
    except KeyError:
        pass #no 'init' section in JSON file, skip

def processTestOnHarmless(args, filename, inst, codeCases, runCases, signature):
    regDict = {'r0':0, 'r1':1, 'r2':2, 'r3':3, 'r4':4, 'r5':5, 'r6':6, 'r7':7,
            'r8':8, 'r9':9,'r10':10, 'r11':11,'r12':12, 'sp':13,'lr':14, 'pc':15}
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
        out.write(signature+' '+str(nbVal)+'\n')
        for codeCase in codeCases:
            oldPC = core.programCounter()
            for runCase in runCases:
                #init
                for reg in runCase:
                    if reg == "cpsr":
                        core.setCPSR(getInt(runCase[reg]['val']))
                    else:
                        regName = codeCase[reg]['idx']
                        if regName != 'pc': #do not update pc, as it won't work.
                            core.gpr_write32(regDict[codeCase[reg]['idx']], getInt(runCase[reg]['val']))
                #exec one instruction
                harmlessPrintReg(core,out)
                out.write('A\n')
                core.execInst(1)
                #print registers
                harmlessPrintReg(core,out)
                out.write('B\n')
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
                    outfile.write(line)
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

def compare(inst, nbVal, testOnTargetOk, filename, gdbOutputLines, instructionIndex):
    ok = 0
    if testOnTargetOk:
        try:
            with open(filename+'_output.harmless') as harmless:
                for line in zip(gdbOutputLines, harmless): #line[0] gdb, line[1] harmless
                    if line[0] != line[1]:
                        ok = 1
        except IOError:
            ok = 2
    else:
        ok = 2
    #report (if no verbose mode, report only if there is a pb).
    if ((args.verbose > 0) and (ok == 0)) or (ok!=0):
        s = max(0,20-len(inst['instruction']))
        print('[{0:3d}'.format(instructionIndex+1), end='')
        if args.verbose > 1:
            print(' - {0:30} - {1:5} cases'.format(filename,nbVal), end='')
        print('] check instruction: '+inst['instruction']+s*' '+'-> ', end='')
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

if __name__ == '__main__':
    #arguments
    parser = argparse.ArgumentParser(description='Check Harmless Cortex ARM model functionnal behavior against a real target')
    parser.add_argument("-nc", "--noclean",
            help="do not remove intermediate files",
            action="store_true", default=False)
    parser.add_argument("-n", "--note",
            help="show test note (if exists)",
            action="store_true", default=False)
    parser.add_argument('-v','--verbose', const=1, default=1, type=int,
              help='The verbose level 0 to 3 (default 1)', nargs='?')
    parser.add_argument("-t", "--target",
            help="run test on target (if required)",
            action="store_true", default=False)
    parser.add_argument('files', metavar='file', nargs='+',
                    help='JSON instruction test spec')
    args = parser.parse_args()

    timeStart = time.clock()
    #0 - read the JSON instruction test
    import json
    nbTests = 0
    nbInstructions = 0
    for filename in args.files:
        with open(filename) as jsonFile:
            inst = json.load(jsonFile)

        #1- generate the object file for Harmless and real target from the JSON test
        codeCases = getSourceFile(filename,inst)
        #2- compile it
        exeFile= compile(args,filename)
        #3- get tests for runtime
        runCases = getRuntimeTests(inst)
        ##4- stats (if verbose mode > 2)
        nbVal = len(codeCases)*len(runCases)
        nbTests += nbVal
        getStats(inst, codeCases, runCases)
        #5- run tests on the real target (if needed)
        testOnTargetOk = False
        gdbOutputLines = readTargetOutputFile(filename)
        shouldBuild, signature = targetOutputFileToBuild(gdbOutputLines) #check with md5
        if shouldBuild:
            testOnTargetOk = processTestOnTarget(args, filename, inst, codeCases, runCases, signature)
            #read the output file (maybe again…)
            gdbOutputLines = readTargetOutputFile(filename)
        else:
            testOnTargetOk = True
            if args.verbose > 2:
                print('tests on target up to date')
        #6- run tests on Harmless
        if testOnTargetOk:
            processTestOnHarmless(args, filename, inst, codeCases, runCases, signature)
        #7- compare
        result = compare(inst, nbVal, testOnTargetOk, filename, gdbOutputLines, nbInstructions)

        #8- is there a note?
        if args.note:
            if 'note' in inst:
                print("\tnote: "+inst['note'])

        ##8- clean (remove tmp files)
        if not args.noclean:
            clean(filename, gdbOutputLines, result)
        nbInstructions += 1
    if args.verbose > 0:
        print(str(nbTests)+' tests done for '+str(nbInstructions)+' instructions in '+
                str(time.clock()-timeStart)+'s\n')
