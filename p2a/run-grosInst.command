#!/bin/sh
set -x
DIR=`dirname $0`
cd $DIR &&
uname -a &&
time ./p2aV2 example/grosInst.config -v -i &&
echo "---------------- SUCCES --------------------------"