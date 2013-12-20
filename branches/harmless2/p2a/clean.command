#!/bin/sh
set -x
DIR=`dirname $0`
cd $DIR &&
make mrproper &&
echo "---------------- SUCCES --------------------------"