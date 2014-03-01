#!/bin/sh
# usage : ./trace_sim_gdb.sh <number>
# code file (.elf) is located in ../build/__gdb.elf
# Generate PSIM output for the first <number> step of execution of <code_file>

GDB=${PPC_XTOOLS}gdb
if [ ! -x $GDB ]; then
	echo "Can't find cross GDB or it isn't executable... aborting"
	exit 1
fi

$GDB -ex "set \$i = $1" -x script_gdb -batch 2>&1|sed '/^[^\#]/d; s/^\#//;1,1d;/^$/d;'
exit 0
