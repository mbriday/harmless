#!/bin/sh

# Test_syntax.sh

# usage : ./test_syntax.sh [<code_file.elf>]
#
# Tests the syntax output of the Harmless simulator.
#  Whitout argument A ramdom binary code file is generated with gen_inst (in the
#  gen_inst/ directory) and is disassembled with both Harmless and objdump. the
#  output are compared with diff. Some errors not caused by harmless description
#  are filtered out by a sed script.
#
# With an argument, the same thing is made but whith the code file given in the
# argument
#
# The scripts need the PPC_XTOOLS environnement variable Exemple : If GCC is in
# ~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-gcc set PPC_XTOOLS to
# "~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-" you may put "export
# PPC_XTOOLS=~/x-tools/powerpc-unknown-elf/bin/powerpc-unknown-elf-" In your shell
# init script ~/.bashrc

# Defines useful constant
# Where are the cross binutils?
OBJDUMP=${PPC_XTOOLS}objdump
OBJCOPY=${PPC_XTOOLS}objcopy

# Size of binary used for the test. A larger Value may make a more accurate test
# but take more time to execute
SIZE=40960

# Output directory
OUT_DIR=./tmp
# Log files
GADL_LOG=${OUT_DIR}/gadl_log
MAKE_LOG=${OUT_DIR}/make_log

# Binary code to test
BIN=${OUT_DIR}/raw_bin.elf

mkdir -p $OUT_DIR

if [ ! -r ../powerpc/powerpc.py ]; then
	echo "Can't find the simulator..."
	echo "Compiling GADL"
	gadl -v  ../ppc.hadl >$GADL_LOG 2>&1

	if [ $? -ne 0 ]; then
		echo "Something got wrong with GAD... Here is the log"
		cat $GADL_LOG;
		exit 1;
	else
		echo "gadl OK"
	fi

# This section can be used to patch the generated sources
# in order to use this :
# call the script once (sources are generated and copied to powerpc_old),
# modify them and then, create a patch file called patch in this directory with
# a diff command or the refresh_patch.sh script (which is configured with default
# values of this script.)

	echo "Saving generated sources"
	rsync -r --delete ../powerpc/ $OUT_DIR/powerpc_old/

	if [ -r patch ]; then
		echo "Applying local patch"
		patch -p0 -d ../powerpc/ < patch
	fi

	echo "Compiling the simulateur"
	make -C ../powerpc >$MAKE_LOG 2>&1

	if [ $? -ne 0 ]; then
		echo "Something got wrong with Make... Here is the log"
		cat $MAKE_LOG
		exit 1
	else
		echo "make OK"
	fi
fi

# Now, the Harmless Simulator is ready


if [ $# -eq  0 -o ! -r $1 ]; then
	# No argument were given to the script or it cannot be read.
	if [ ! -x ./gen_inst/gen_inst ]; then
		echo "Can't find gen_inst or it isn't executable... aborting"
		exit 1
	fi
	echo "Generating binary"
	./gen_inst/gen_inst $SIZE $OUT_DIR/raw_bin

# ...in ELF format using objcopy
	if [ ! -x $OBJCOPY ]; then
		echo "Can't find objcopy in $OBJCOPY or it isn't executable... aborting"
		exit 1
	fi

	$OBJCOPY -I binary -O elf32-powerpc -B powerpc --rename-section .data=.text --set-start 0 $OUT_DIR/raw_bin $BIN
else
	# use the given test file
	echo "Binary file selected : $1"
	BIN=$1
fi

echo "Desassembly with Harmless simulator"
./deasm.py $BIN $SIZE > $OUT_DIR/simu_asm


if [ ! -x $OBJDUMP ]; then
	echo "Can't find objdump in $OBJDUMP or it isn't executable... aborting"
	exit 1
fi

echo "Desassembly with Objdump"
# Generate output of objdump and filter out useless lines
$OBJDUMP -D $BIN -M 32 \
|cut -f 3 | sed "1,7d;s/\s\+/ /;s/\s*<.*>//"\
|sed "/^[0-9a-fA-F]*:$/d" |sed "/^\s*$/d"|sed "/^Disassembly/d" > $OUT_DIR/objdump_asm
# We cut off the offset, the header and the symbolic search from objdump to
# match Harmless simulator output.

echo '========== Comparison ==========='
diff $OUT_DIR/objdump_asm $OUT_DIR/simu_asm -y |expand > $OUT_DIR/diff_dump
cat $OUT_DIR/diff_dump |head -n 20
echo "..."
cat $OUT_DIR/diff_dump | wc -l | sed "s/^/=========== /; s/$/ lines ============/;"
echo '========== Difference ============'
diff $OUT_DIR/objdump_asm $OUT_DIR/simu_asm -y --suppress-common-lines \
		|sed "/\.long/d"\
		|sed "/^doz\|^stdu\|^rld\|^td\|^ld\|^rlmi\|^std\|^rldicr\|^rldimi\|^srad\|^lwa\|^v\|^maskir\|^sriq\|^rotld\|^tlbsx\|^rac\|^dss\|^dcba\|^fsqrt\|^tlbia\|^cntlzd\|^divd\|^divdu\|^extsw\|^fcfid\|^fctid\|^fctidz\|^ldarx\|^lwa\|^mtmsrd\|^mtsrd\|^mulld\|^mulhd\|^rldcl\|^rldcr\|^rldic\|^rldimi\|^slbia\|^slbie\|^sld\|^srad\|^srd\|^std\|^stv\|^tlbr\|^mtv\|^sre\|^slq\|^sle\|^lv\|^srai\|^lsc\|^clrld\|^rr\|^icbt\|^ma\|^slb\|^sli\|^sraq\|^srq\|^mfv\|clcs\|^wrtee/d" \
		|expand > $OUT_DIR/difference
# this removes opcodes that are not recognized by Objdump and opcodes that are not implanted in the MCP750

cat $OUT_DIR/difference \
		|head -n 20 \
		||true
echo "..."
cat $OUT_DIR/difference | wc -l | sed "s/^/=========== /; s/$/ fails ==============/;"

