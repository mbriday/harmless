#!/bin/sh
# CALLED FROM ../test_behavior.py
# usage : ./trace_sim_gdb.sh <code_file> <number>
# Generate internal gdb simulator output for the first <number> step of execution of <code_file>

GDB=${ARM_XTOOLS}gdb
if [ ! -x $GDB ]; then
	echo "Can't find cross GDB or it isn't executable... aborting"
	exit 1
fi

#get start address.
OBJDUMP=${ARM_XTOOLS}objdump
START=`$OBJDUMP -f $1 | grep ^start\ address | awk '{ print $3; }'`

#generate the gdb script (nb loops, file name, start address)
sed "s/\@LOOP\@/$2/;s|\@FILE\@|$1|;s/\@START\@/$START/" script_gdb.template > ../tmp/script_gdb
#$GDB -ex "set \$i = $2" -se $1 -x script_gdb -batch 2>&1| tee ../tmp/gdblog |sed '/^[^\#]/d; s/^\#//;1,1d;/^$/d;'
# filter:
# - remove first 7 lines (gdb preamble)
# - remove lines beginning with 0x -> address with symbol.
# - remove lines beginning with a letter (or '_') -> symbol
# - remove lines that do not end with an hexa value (0-9, a-f)
#$GDB -ex "set \$i = $2" -se $1 -x script_gdb -batch 2>&1| tee ../tmp/gdblog | sed "1,7d;/^0x.*$/d;/^[a-zA-Z_].*$/d;/[^0-9a-f]$/d"
$GDB -x ../tmp/script_gdb -batch 2>&1 | tee ../tmp/gdblog | sed "1,7d;/^\([0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][,]\)/! d"
exit 0
