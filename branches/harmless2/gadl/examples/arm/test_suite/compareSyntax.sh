#!/bin/sh

#${ARM_XTOOLS}objcopy -I binary -O elf32-littlearm -B arm --rename-section .data=.text --set-start 0 randInst randInst.elf

#cd .. && gadl ./arm_iss_32.hadl -c && cd arm && make python -j 1 && cd ../test_suite &&
#from the objdump output file:
# replace tabs to spaces (expand)
# remove line 1..6 (preamble)
# remove <label> (in jumps)
# remove comments (after the ';')
# remove empty lines
# remove lines with a label: 'address
# remove spaces at end of line.
# translate from uppercase to lowercase.
# remove the 'ia' in ldmia and stmia instructions (this is implicit in armv7)

#FILE=./a.out
#FILE=./randInst.elf
FILE=./rand_inst.elf

#${ARM_XTOOLS}objdump -D ${FILE} | expand -t1 | sed "1,6d;s/\s*<.*>//;s/;.*$//" | sed "/^[0-9a-fA-F]* :$/d" | sed "/^\s*$/d" | sed "s/\ *$//" | tr "[:upper:]" "[:lower:]" > temp2.txt && 
/usr/local/arm/bin/arm-eabi-objdump -D ${FILE} | expand -t1 | sed "1,6d;s/\s*<.*>//;s/;.*$//" | sed "/^[0-9a-fA-F]* :$/d" | sed "/^\s*$/d" | sed "s/\ *$//" | tr "[:upper:]" "[:lower:]" | sed "s/ldmia/ldm/g" | sed "s/stmia/stm/g"> temp2.txt && 

#nb of lines
./deasm.py ${FILE} `sed -n '$=' temp2.txt` | tr "[:upper:]" "[:lower:]" > temp1.txt &&
#There is a bug in objdump:
# instruction with '[pc], #val' with a negative value => the '-' is not printed.
# these instructions are removed.
#diff temp?.txt -y --suppress-common-lines | sed /stall/d | sed /error/d | sed "/\[pc\], #-/d" > diffT.txt
diff temp?.txt -y --suppress-common-lines | sed /stall/d | sed /error/d | sed "/.word/d" > diffT.txt
#diff temp?.txt -y --suppress-common-lines | sed /undefined/d | sed /ERROR/d > diffT.txt
#cmnp, tstp, teqp and cmpp are obsolete: not decoded in harmless
sed -e '/cmnp/d; /cmn..p/d; /cmpp/d; /cmp..p/d; /tstp/d; /tst..p/d; /teqp/d; /teq..p/d ' <diffT.txt >diff.txt && rm diffT.txt
#diff temp?.txt -y --suppress-common-lines | sed /undefined/d > diff.txt
if [ -s diff.txt ]; then #file exists and is not empty
  cat diff.txt
  wc -l diff.txt
fi
#vimdiff temp?.txt

