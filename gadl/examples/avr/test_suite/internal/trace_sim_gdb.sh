#!/bin/sh
# CALLED FROM ../test_behavior.py
# usage : ./trace_sim_gdb.sh <code_file> <number>
# Generate simulavr output for the first <number> step of execution of <code_file>

GDB=${AVR_XTOOLS}gdb
SIMULAVR=simulavr #TODO:should be in the path :-/

if [ ! -x $GDB ]; then
	echo "Can't find cross GDB or it isn't executable... aborting"
	exit 1
fi
$SIMULAVR -p 3239 --gdbserver -d atmega128 $1 >/dev/null 2>&1 &
sleep 1 #TODO test that simulavr is listening, instead of waiting
$GDB -ex "set \$i = $2" -se $1 -x ./internal/script_gdb -batch 2>&1 | tee ./tmp/gdblog |sed '/^[^\#]/d; s/^\#//;1,1d;/^$/d;'
killall $SIMULAVR 2>/dev/null
exit 0
