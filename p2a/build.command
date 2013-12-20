#!/bin/sh
set -x
DIR=`dirname $0`
cd $DIR &&
make "OPTIM=1" &&
echo "---------------- SUCCES --------------------------"