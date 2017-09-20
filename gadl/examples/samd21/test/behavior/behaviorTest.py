#! /usr/bin/env python
# -*- coding: UTF-8 -*-

import sys, os
import subprocess
import argparse
import shutil

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

def debug(group):
    print(str(len(group))+' entries:')
    print(group)
    with open("test.json", "w") as outfile:
        json.dump(group, outfile, indent=4)

#the 'forCode' boolean is used to determine if the combinations
#are used for the code generation, or the functionnal eval.
#in the first case, we do not need to give all combinations,
# (if we modify xPSR, the mnemonic is unchanged).
def combinations(inst, forCode):
    #first, get all cases for each register
    group = []
    for key in ['src', 'dest']:
        if forCode:
            getRegCombinationsForCode(inst,group,key)
        else:
            getRegCombinationsForRuntime(inst,group,key)
    #debug(group)
    
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
        for idf in ('idx','imm'):
            if idf in case[reg]:
                mnemo = mnemo.replace('{'+reg+'}',str(case[reg][idf]))
    return mnemo

def getSourceFile(filename, inst):
    with open(filename+'.s',"w") as asm:
        asm.write(".text\n")
        asm.write(".syntax unified\n")
        asm.write(".thumb\n")
        asm.write(".global _start\n")
        asm.write("_start:\n")
        codeCases = []
        for case in combinations(inst,True):
            codeCases.append(case)
            asm.write('\t'+extractMnemo(inst,case)+'\n')
        asm.write("\tb .\n") #while(1);
        return codeCases

def compile(args,sourceFile):
    #asm
    if args.verbose:
        print("compile file "+sourceFile+'.s')
    objFile = sourceFile+".o"
    returnCode = subprocess.call(["arm-none-eabi-as", "-mthumb", "-mcpu=cortex-m4", sourceFile+'.s', "-o", objFile])
    if returnCode != 0:
        print("*** Assembling, error " + str(returnCode) + " ***\n")
        sys.exit(returnCode)
    #link
    exeFile = sourceFile+".elf"
    if args.verbose:
        print("link file to "+exeFile)
    returnCode = subprocess.call(["arm-none-eabi-ld", objFile, "-o", exeFile, "-Tscript.ld"],)
    if returnCode != 0:
        print("*** Linking, error " + str(returnCode) + " ***\n")
        sys.exit(returnCode)
    return exeFile

def getRuntimeTest(inst):
    runCases = []
    for case in combinations(inst,False):
        runCases.append(case)
    return runCases

def prepareTestCaseForGdb(codeCase, runCase, gdb):
    for reg in runCase:
        if reg == "cpsr":
            gdb.write('set $cpsr='+str(runCase[reg]['val'])+'\n')
        else:
            gdb.write('set $'+str(codeCase[reg]['idx'])+'='+str(runCase[reg]['val'])+'\n')

    
def generateGdbScript(filename, inst, codeCases, runCases):
    with open(filename+'.gdb',"w") as gdb:
        gdb.write("tar extended-remote :4242\n")
        gdb.write("set interactive-mode off\n")
        gdb.write("load\n")
        gdb.write("define dumpRegs\n")
        for i in range(13):
            gdb.write('\tprintf "0x%x\\t",$r'+str(i)+'\n')
        gdb.write('\tprintf "0x%x\\t",$sp\n')
        gdb.write('\tprintf "0x%x\\t",$lr\n')
        gdb.write('\tprintf "0x%x\\t",$pc\n')
        gdb.write('\tprintf "0x%x\\t\\n",$cpsr\n')
        gdb.write('end\n\n')

        gdb.write('set logging file '+filename+'_output.gdb\n')
        gdb.write('set logging redirect on\n')
        gdb.write('set logging on\n\n')

        for codeCase in codeCases:
            #first time
            gdb.write('set $oldpc = $pc\n')
            #prepare the case, with run time info
            for runCase in runCases:
                prepareTestCaseForGdb(codeCase, runCase, gdb)
                #then run the case
                gdb.write('set logging off\n')
                gdb.write('si\n')
                gdb.write('set logging on\n')
                #and get back register state.
                gdb.write('dumpRegs()\n\n')
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

def checkTargetOutputFile(filename):
    """ This function checks that the target output file exists, and then
        - read the first line => that stores the md5 of the JSON file
        - compare it with the JSON file of the test
        - if they differ, the test have been updated and the test should be done again.
    """ 
    pass


if __name__ == '__main__':
    #arguments
    parser = argparse.ArgumentParser(description='Check Harmless Cortex ARM model functionnal behavior against a real target')
    parser.add_argument("-v", "--verbose",    
            help="be verbose…",
            action="store_true", default=False)
    args = parser.parse_args()
    
    #0 - read the JSON instruction test
    import json
    filename = 'beh_lsl.json'
    with open(filename) as jsonFile:
        insts = json.load(jsonFile)

    for inst in insts:
        #1- generate the object file for Harmless and real target from the JSON test
        codeCases = getSourceFile(filename,inst)
        #2- compile it
        exeFile= compile(args,filename)

        #3- get tests for runtime
        runCases = getRuntimeTest(inst)
        if args.verbose:
            print("code to test instruction "+inst['instruction']+" requires:")
            print("\t"+str(len(codeCases))+" instructions in the code ("+str(len(codeCases)*inst['size'])+" bytes for the program)")
            print("\t"+str(len(runCases))+" tests for each instruction => "+str(len(codeCases)*len(runCases))+" cases")
        #4- generate the gdb script
        generateGdbScript(filename, inst, codeCases, runCases)
    
