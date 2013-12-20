#!/bin/sh
# CALLED FROM ../test_behavior.py
# usage : ./trace_sim_gdb.sh <code_file> <number>
# Generate internal gdb simulator output for the first <number> step of execution of <code_file>

GDB=${ARM_XTOOLS}gdb
if [ ! -x $GDB ]; then
	echo "Can't find cross GDB or it isn't executable... aborting"
	exit 1
fi
# filter:
# - remove all except (/32): 0x-------- format
# - juste keep --------- part
# - add ',' at the end of each line
# - group lines by 36
$GDB -ex "set \$i = $2" -se $1 -x script_gdb_lpc -batch 2>&1| tee ../tmp/gdblog | sed "/(\/32): 0x[0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F]/! d" | cut -d"x" -f2 | sed 's/$/,/' | sed '$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;$!N;s/\n//;'
exit 0
