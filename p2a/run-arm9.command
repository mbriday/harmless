#!/bin/sh
set -x
DIR=`dirname $0`
cd $DIR &&
time ./p2aV2 example/arm9.config -v -i &&
echo "---------------- SUCCES --------------------------"