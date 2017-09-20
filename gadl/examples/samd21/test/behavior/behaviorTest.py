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

def getRegCombinations(inst,group,key, forCode):
    # for each reg, get the possible combinaisons 
    # (each value, for each reg index).
    if key in inst:
        for regName in inst[key]:
            reg = inst[key][regName]
            case = []
            if 'idx' in reg:
                for idxTxt in reg['idx']:
                    idx = getInt(idxTxt)
                    if forCode:
                        case.append({'idx':idx})
                    else:
                        if 'val' in reg:
                            for valTxt in reg['val']:
                                val = getInt(valTxt)
                                case.append({'val':val, 'idx':idx})
            elif 'val' in reg and not forCode: #no idx => maybe APSR
                for valTxt in reg['val']:
                    val = getInt(valTxt)
                    case.append({'val':val})
            if 'imm' in reg:
                for immTxt in reg['imm']:
                    imm = getInt(immTxt)
                    case.append({'imm':imm})
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
        getRegCombinations(inst,group,key, forCode)
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

def getSourceFile(filename, insts):
    with open(filename+'.s',"w") as asm:
        asm.write(".text\n")
        asm.write(".syntax unified\n")
        asm.write(".thumb\n")
        asm.write(".global _start\n")
        asm.write("_start:\n")
        for inst in insts:
            for case in combinations(inst,True):
                asm.write('\t'+extractMnemo(inst,case)+'\n')
        asm.write("\tb .\n") #while(1);

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

    #1- generate the object file for Harmless and real target from the JSON test
    getSourceFile(filename,insts)

    #2- compile it
    exeFile= compile(args,filename)



##faire le fichier de mnemoniques.
#for inst in insts:
#    for case in combinations(inst,True):
#        print(extractMnemo(inst,case))
