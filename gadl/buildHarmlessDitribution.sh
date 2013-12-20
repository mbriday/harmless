#!/bin/sh
#based on P.Molinaro's shell script to build Piccolo :-)
#set -x
#-------------------- Harmless Version
VERSION=`cat galgas_sources/gadl_program.gProgram | grep "version" | awk '{ print $4}' | sed s/\"://g` &&
#VERSION_STR=${VERSION} | sed 's/\./_/g' && 
#echo "${VERSION_STR}" &&
#-------------------- remove previous distribution
DIR=`pwd`/Distribution_Harmless_${VERSION} &&
XCODE_CONFIG=Default &&
rm -fr ${DIR} &&
#-------------------- build directory
mkdir ${DIR} &&
#-------------------- build libpm distribution (dos and unix) and store rev number in info-libpm.txt
#echo "-> build libpm source archives..." &&
#cp -r ../libpm ${DIR}/libpm &&
cd ${DIR} && ln -s ../../libpm libpm &&
#eolc -dos -D${DIR}/libpm -Eh -Ec -Ecpp -Em -Emm -Emak -Ebat >/dev/null&&
#cd ${DIR} && tar c libpm | bzip2 -9 > libpm-crlf.tar.bz2 &&
#build unix in last, because it will be used in the compilation process.
#eolc -unix -D${DIR}/libpm -Eh -Ec -Ecpp -Em -Emm -Emak -Ebat >/dev/null&&
#cd ${DIR} && tar c libpm | bzip2 -9 > libpm-lf.tar.bz2 &&
#-------------------- Import Harmless and store rev number in info-Harmless.txt
echo "-> import last release of Harmless (SVN) ..." &&
svn export https://p2a.rts-software.org/svn/gadl ${DIR}/Harmless | grep "Exported revision" | awk '{ print $3; }'  | sed "s/\.//g" > ${DIR}/info-Harmless.txt &&
#----- Update version numbers (based on SVN rev of Harmless and libpm and Harmless version in gadl_program.ggs
BUILD_VERSION="build `cat ${DIR}/info-Harmless.txt`" &&
#sed s/BUILD_AND_LIBPM/"$BUILD_VERSION"/g ${DIR}/Harmless/project_xcode/Info.plist > ${DIR}/temp &&
#mv ${DIR}/temp ${DIR}/Harmless/project_xcode/Info.plist &&
sed "s@HARMLESS_VERSION@$VERSION@g" ${DIR}/Harmless/project_xcode/English.lproj/InfoPlist.strings > ${DIR}/temp &&
mv ${DIR}/temp ${DIR}/Harmless/project_xcode/English.lproj/InfoPlist.strings &&
#-------------------- Build source archive of Harmless
echo "-> build Harmless source and examples archives ..."
eolc -dos -D${DIR}/Harmless -Eh -Ec -Ecpp -Em -Emm -Ehh -Ebat -Emak -Fmakefile >/dev/null &&
cd ${DIR} && tar c Harmless | bzip2 -9 > Harmless-sources-crlf.tar.bz2 &&
cd ${DIR}/Harmless && tar c examples | bzip2 -9 > ${DIR}/examples-crlf.tar.bz2 &&
eolc -unix -D${DIR}/Harmless -Eh -Ec -Ecpp -Em -Emm -Ehh -Ebat -Emak -Fmakefile >/dev/null &&
cd ${DIR} && tar c Harmless | bzip2 -9 > Harmless-sources-lf.tar.bz2 &&
cd ${DIR}/Harmless && tar c examples | bzip2 -9 > ${DIR}/examples-lf.tar.bz2 &&
#-------------------- galgas the Harmless sources.
echo "-> generate Harmless c++ files (galgas) ..." &&
cd ${DIR}/Harmless/galgas_sources/ && galgas --new-code-generation all_gadl.gProject &&
#-------------------- generate an archive of the templates (cr-lf and lf)
echo "-> get templates archives..." &&
eolc -dos -D${DIR}/Harmless/templates -Eh -Ec -Ecpp -Em -Emm -Emak -Ebat >/dev/null&&
cd ${DIR}/Harmless && tar c templates | bzip2 -9 > ${DIR}/Harmless-templates-crlf.tar.bz2 &&
#  build unix in last, because it will be used in the compilation process.
eolc -unix -D${DIR}/libpm -Eh -Ec -Ecpp -Em -Emm -Emak -Ebat >/dev/null&&
cd ${DIR}/Harmless && tar c templates | bzip2 -9 > ${DIR}/Harmless-templates-lf.tar.bz2 &&
#-------------------- Build x86-linux executable
echo "-> build Linux version ..." &&
cd ${DIR}/Harmless/makefile_x86linux_on_macosx/ && make -f makefile gadl -j2 >/dev/null&&
cd ${DIR}/Harmless/makefile_x86linux_on_macosx/ && zip -9 Harmless.zip gadl >/dev/null&&
cp ${DIR}/Harmless/makefile_x86linux_on_macosx/Harmless.zip ${DIR}/Harmless-i386-linux.zip &&
#-------------------- Build MSWindows executable
echo "-> build Windows version ..." &&
cd ${DIR}/Harmless/makefile_mingw_on_macosx/ && make -f makefile gadl.exe -j2 >/dev/null &&
cp ${DIR}/Harmless/makefile_mingw_on_macosx/gadl.exe ${DIR}/Harmless.exe &&
cd ${DIR} && bzip2 -9 Harmless.exe &&
#-------------------- Build MacOSX Universal Binary and Cocoa editor.
echo "-> build MacOs X version (universal binary, including the description editor) ..." &&
cd ${DIR}/Harmless/project_xcode && xcodebuild -alltargets -configuration ${XCODE_CONFIG} >/dev/null &&
mkdir ${DIR}/Cocoa-Harmless&&
#cp ${DIR}/Harmless/AUTHORS ${DIR}/Cocoa-Harmless &&
#cp ${DIR}/Harmless/COPYING ${DIR}/Cocoa-Harmless &&
mv ${DIR}/Harmless/project_xcode/build/${XCODE_CONFIG}/CocoaGadl.app ${DIR}/Cocoa-Harmless/Harmless.app &&
hdiutil create -srcfolder ${DIR}/Cocoa-Harmless ${DIR}/cocoa-Harmless.dmg >/dev/null&&
rm -fr ${DIR}/Cocoa-Harmless &&
#-------------------- Creer l'archive de l'outil ligne de commande pour mac
mkdir ${DIR}/Harmless-Mac-UniversalBinary &&
#cp ${DIR}/Harmless/AUTHORS ${DIR}/Harmless-Mac-UniversalBinary &&
#cp ${DIR}/Harmless/COPYING ${DIR}/Harmless-Mac-UniversalBinary &&
mv ${DIR}/Harmless/project_xcode/build/${XCODE_CONFIG}/gadl ${DIR}/Harmless-Mac-UniversalBinary/Harmless &&
hdiutil create -srcfolder ${DIR}/Harmless-Mac-UniversalBinary ${DIR}/Harmless-tool.dmg >/dev/null&&
rm -fr ${DIR}/Harmless-Mac-UniversalBinary &&
#-------------------- Copier changeLog.html
#mv ${DIR}/Harmless/changeLog.html ${DIR}/changeLog.html &&
#-------------------- Supprimer les repertoires sources
cd ${DIR} &&
rm -fr ${DIR}/libpm &&
rm -fr ${DIR}/Harmless &&
echo "all generated files are in directory: ${DIR}" &&
scp ${DIR}/* irccyn@irccyn.typhon.net:projets/p2a/www/tmp/upload &&
echo "-------------- SUCCESS ---------------" ||
echo "-------------- FAILED ----------------"
