#! /usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys, os
import subprocess
import argparse
import shutil

def getSourceFile(args, buildDir):
    if args.file: #there is a sourceFile
        if not os.path.exists(args.file):
            print("file '"+args.file+"' does not exists")
            sys.exit(1)
        shutil.copy(args.file, buildDir)
        src = os.path.join(buildDir,args.file)
    else: #no source file. Generate it
        src = os.path.join(buildDir,"__asmFile.s")
        if args.verbose:
            print("Generate the source file "+src+
                    " with opcodes from "+str(args.fromRange)+" to "+str(args.toRange)+".")
        s =  ".text\n"
        s += ".syntax unified\n"
        s += ".global _start\n"
        s += "_start:\n"
        for i in range(args.fromRange, args.toRange) :
            if i > 0xffff:
                val = (i>>16) | ((i & 0xffff) << 16) #hword order.
                #s += "\t.hword " + hex (i>>16) + "\n"
                #s += "\t.hword " + hex (i & 0xffff) + "\n"
                s += "\t.word " + hex (val) + "\n"
            else:
                s += "\t.hword " + hex (i) + "\n"
        f = open (src, "w")
        f.write (s)
        f.close ()
    return src    

def compile(args,sourceFile):
    #asm
    if args.verbose:
        print("compile file "+sourceFile)
    objFile = sourceFile+".o"
    returnCode = subprocess.call(["arm-none-eabi-as", "-mthumb", "-mcpu=cortex-m4", sourceFile, "-o", objFile])
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

def objdump(args,exeFile):
    #objdump
    objdumpFile = exeFile+".objdump"
    f = open (objdumpFile, 'w')
    if args.verbose:
        print("generate objdump dump file to "+objdumpFile)    
    returnCode = subprocess.call(["arm-none-eabi-objdump", "-Mforce-thumb", "-Mreg-names-std", "-D", exeFile], stdout = f)
    f.close()
    if returnCode != 0:
        print("*** Objdump, error " + str(returnCode) + " ***\n")
        sys.exit(returnCode)
    return objdumpFile

def harmless(args,exeFile):
    sys.path.append("../../samd21")
    harmlessFile = exeFile+".harmless"
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
    core = sam.getCore(0)
    core.readCodeFile(exeFile)
    f = open (harmlessFile, "w")
    if args.verbose:
        print("generate harmless dump file to "+harmlessFile)    
    rangeD = args.toRange-args.fromRange
    f.write(core.disassemble(core.programCounter(),rangeD,True)+'\n');
    f.close()
    return harmlessFile

def clean(args, buildDir):
    if args.clean:
        if args.verbose:
            print("remove build directory "+buildDir)
        shutil.rmtree(buildDir)

def getIntOpcode(string):
    try:
        if len(string) < 5:
            return int(string[0:4],16)
        else:
            return int(string[0:4],16) << 16 | int(string[5:9],16)
    except Exception:
        print("error in integer conversion: "+string)
        return 0

def isException(dataO, dataH):
    exception = 0;
    opcode = getIntOpcode(dataO[0]) #convert opcode into an int.
    #print 't',opcode
    if dataO[1] == "" and dataH[1][0:5] == "Stall": #no mnemonic for that code.
        exception = 1
    elif dataO[1] == "" and dataH[1][0:9] == "no syntax": #no mnemonic for that code.
        exception = 2
    elif dataO[0][0] == "b" and dataO[0][1] == 'f' and dataO[0][3] == '0':
        #arm 16 bits hints instructions => bf-0
        exception = 3
    elif dataO[0][0:3] == "c00":
        #'stmia<und>	r0!, {}' for c00- => objdump adds the <und>, instruction is undefined.
        exception = 4
    elif opcode & 0xfff0f000 == 0xe840f000:
        #Load store exclusive with Rt=PC => unpredictable, but objdump says 'tt', 'tta', 'ttat', …
        exception = 5
    elif ((opcode > 0xffff) and (opcode & 0xffdf0000 == 0xf80f0000)) or (opcode & 0xffdf == 0xf80f): #strb, strh
        #Store with Rn = pc is unpredictable… and objdump tries to parse it.
        exception = 6
    elif ((opcode > 0xffff) and (opcode & 0xffff0000 == 0xf84f0000)) or (opcode & 0xffff == 0xf84f): #str
        #Store with Rn = pc is unpredictable… and objdump tries to parse it.
        exception = 6
    elif dataH[1].find("invalid") >= 0:
        exception = 7
    elif dataO[1].find("undefined") >= 0:
        exception = 8
    elif dataO[1].find("unknown") >= 0:
        exception = 9
    elif dataO[1].find("UNDEF") >= 0:
        exception = 10
    elif ((opcode > 0xffff) and (opcode & 0xfedf0f00 == 0xf81f0e00)): #ldr(s)(b|h)t should have Rn!=15
        #ldrbt impose that Rn != 15 (this is a ldrb.w in that case), but objdump does not
        exception = 11
    elif ((opcode > 0xffff) and (opcode & 0xfff0f900 == 0xf810f900)): #p.A5.146 => op1=0, op2=1xx1xx unpredictable
        #but objdump understand it as a pld [rn], #imm instruction.
        exception = 12
    elif ((opcode > 0xffff) and (opcode & 0xfef0ff00 == 0xf810fe00)): #p.A5.146 => op1=x0, op2=1110xx unpredictable
        exception = 13
    elif ((opcode > 0xffff) and (opcode & 0xfed0f900 == 0xf810f900)): #p.A5.146 => op1=x0, op2=1xx1xx unpredictable (byte+half)
        exception = 14
    elif ((opcode > 0xffff) and (opcode & 0xfe70f000 == 0xf830f000)): #p.A5.146 => Rt never set to 0xF => unpredictable.
        exception = 15
    elif ((opcode > 0xffff) and (opcode & 0xffff0000 == 0xf85f0000)): #p.A5.144 => ldrt without Rn=0xf (objdump error)
        exception = 16
    elif ((opcode > 0xffff) and (opcode & 0xff700000 == 0xf9500000)): #p.A5.144 => ldr with op1 > 1 => unpredictable.
        exception = 16
#    elif ((opcode > 0xffff) and (opcode & 0xfff0f000 == 0xf830f000)): #p.A5.145 =>  no pldw with halfwords
#        exception = 15
#    elif ((opcode > 0xffff) and (opcode & 0xfff0f000 == 0xf8b0f000)): #p.A5.145 =>  no pldw with halfwords
#        exception = 15
#    elif ((opcode > 0xffff) and (opcode & 0xfff0ff00 == 0xf930fc00)): #p.A5.145 => op1=10, op2=1100xx Rt=f unpredictable (byte+half)
#        exception = 16
    #print('opcode: '+hex(opcode)+', '+str(exception))
    return (exception != 0)

import re
def compare(args, objdumpFile, harmlessFile):
    #1 - read harmless dump
    dictHarmless = {}
    dictObjdump = {}
    h = open (harmlessFile, "r")
    p=re.compile('.*0x([0-9a-fA-F]+)\s+:([0-9a-fA-F\ ]+) : (.*)$')
    for line in h:
        m=p.match(line)
        address = m.groups()[0]
        opcode  = m.groups()[1].strip()
        mnemo   = m.groups()[2]
        dictHarmless[address] = (opcode,mnemo)
    h.close()
    #2 - read objdump dump
    h = open (objdumpFile, "r")
    #example: 0 => address, 2041 => opcode,  movs… => mnemo, ';' => comment.
    #0:	2041      	movs	r0, #65	; 0x41
    p=re.compile('\s*([0-9a-fA-F]+):\s*([0-9a-fA-F\ ]+)\s+([^;\n]*).*$')
    for line in h:
        m=p.match(line)
        if m:
            address = m.groups()[0]
            opcode  = m.groups()[1].strip()
            mnemo   = m.groups()[2].strip()
            dictObjdump[address] = (opcode,mnemo)
    h.close()
    #3 - compare+results
    miss = 0
    exceptions = 0
    total = 0
    for address,dataH in dictHarmless.items():#iteritems in python 2.xx
        if address in dictObjdump:
            total = total+1
            #ok, address are matching.
            dataO = dictObjdump[address]
            if dataO[0][0:3] != dataH[0][0:3]: #opcode mismatch
                #maybe interpreted as 16 bits in one disassembler, and 32 bits in other…
                print('data0 '+dataO[1])
                print("error at address "+address+". Opcode does not match:\n")
                print("\tHarmless opcode: '"+dataH[0]+"'")
                print("\tobjdump  opcode: '"+dataO[0]+"'")
            #compare mnemonics
            if dataO[1] != dataH[1]:
                if isException(dataO,dataH): #Is this a special case?
                    exceptions = exceptions+1
                else: #comparison failed and it's not an exception
                    if miss < 100:
                        print("@"+address+", opcode "+dataO[0]+" => h:'"+dataH[1]+"'\to:'"+dataO[1]+"'")
                    miss = miss+1
    if miss >= 100:
        print("Only the first 100 errors are displayed.")
        print("fix the problem and check in range: -fr "+hex(args.fromRange)+" -tr "+hex(args.toRange))
    if miss == 0:
        if args.verbose:
            print("Great! No error out of "+str(total)+" comparisons.")
            print("       "+str(exceptions)+" exceptions used ("+str(float(1000*exceptions/total)/10)+"%).")
    else:
        print("results: "+str(miss)+" comparisons failed, out of "+str(total)+": success = "+str((float(1000*(total-miss)/total))/10)+"%.")
    return miss

def auto_int(x):    #used for argument parsing, it detects the base. It allows to use hexadecimal arguments.
    return int(x, 0)

if __name__ == '__main__':
    #arguments
    parser = argparse.ArgumentParser(description='Check Harmless disassembler against the objdump output (Cortex 16 bits ASM)')
    parser.add_argument("-v", "--verbose",    
            help="be verbose…",
            action="store_true", default=False)
    parser.add_argument("-n", '--noHarmless', 
            help='do not run the harmless disassembler (objdump only)',
            action="store_true", default=False)
    parser.add_argument("-f", "--file",
            help="use asm FILE for comparison. Il no file is defined, generate a file with all the opcodes in a range "+
            "(with --fromRange and --toRange parameters)")
    parser.add_argument("-fr", "--fromRange",
            help="compare Harmless with objdump with opcodes range starting from FROMRANGE. Default 0",
            type=auto_int, default=0)
    parser.add_argument("-tr", "--toRange", 
            help="compare Harmless with objdump with opcodes range starting from TORANGE. Default to 0xdfff",
            type=auto_int, default=0xdfff)
    parser.add_argument("-c", "--clean",    
            help="remove intermediate files at the end of comparison", 
            action="store_true",default=False)
    parser.add_argument("-b", "--buildSubDir", 
            help="build subdirectory (of 'build'). Useful if many instances are used.",
            type=str, default="build0")
    args = parser.parse_args()
    if args.toRange < args.fromRange:
        print('invalid range: toRange parameter should be greater than fromRange')
        sys.exit(1)

    #0 le dossier de build
    buildDir = os.path.join('./build', args.buildSubDir)
    if os.path.exists(buildDir):
        shutil.rmtree(buildDir)
    os.makedirs(buildDir)

    #1- get the file to compare with.
    sourceFile= getSourceFile(args, buildDir) #source file without the extension
    
    #2- compile it.
    exeFile= compile(args,sourceFile)

    #3- objdump generation
    objdumpFile= objdump(args,exeFile)
    
    miss = 0
    if not args.noHarmless:
        #4- harmless generation
        harmlessFile= harmless(args,exeFile)

        #5- compare
        miss = compare(args, objdumpFile, harmlessFile)
    #clean
    clean(args, buildDir)
    if miss:
        sys.exit(1)
    
