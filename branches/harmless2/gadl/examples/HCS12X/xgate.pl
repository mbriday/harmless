#!/usr/bin/perl

# replace a string in file.
#arg1 -> file to update
#arg2 -> string to remove
#arg3 -> string to set instead
sub remplace {
	my $fichier=$_[0];	
	my $strOld =$_[1];	
	my $strNew =$_[2];	
	open(FICH_OLD, $fichier) || die "Erreur d'ouverture de fichier";
	open(FICH_NEW,">$fichier.tmp") || die ("Erreur de creation de fichier") ;
	foreach $ligne (<FICH_OLD>)
	{
		#if($ligne =~ s/$strOld/$strNew/g) {print "ok\n";}
		$ligne =~ s/$strOld/$strNew/g;
		print FICH_NEW $ligne;
	}
	close FICH_NEW;
	close FICH_OLD;
	system("mv $fichier.tmp $fichier");
}

#system("gadl ./XGate.hadl");

##### first, replace each occurence of 'arch' by 'xgate' (due to conflict with hc12's arch).
@cpp = <./XGate/*.cpp>;
@h   = <./XGate/*.h>;
foreach $src    (@cpp) {&remplace($src   , arch, xgate);}
foreach $header (@h)   {&remplace($header, arch, xgate);}
system("mv ./XGate/arch.cpp ./XGate/xgate.cpp");
system("mv ./XGate/arch.h ./XGate/xgate.h");

#install storage wrapper.
&remplace('./XGate/xgate.h', 'rwStorage \*mem_XGMEMChunk', 'xgateStorage *mem_XGMEMChunk');
&remplace('./XGate/xgate.h', '#include "storage.h"', "#include \"storage.h\"\n\#include \"../xgateStorage.h\"");
&remplace('./XGate/xgate.h', 'storage \* getProgramChunk', 'xgateStorage * getProgramChunk');
&remplace('./XGate/xgate.h', 'storage \* mem_getChunk', 'xgateStorage * mem_getChunk');
&remplace('./XGate/xgate.h', 'roStorage \*codeMem = \(roStorage ', 'xgateStorage *codeMem = (xgateStorage ');
&remplace('./XGate/xgate.cpp', 'roStorage \*ro = \(roStorage \*\)mem', 'xgateStorage *ro = (xgateStorage *)mem');
&remplace('./XGate/xgate.cpp', 'rwStorage \*rw = \(rwStorage \*\)mem', 'xgateStorage *rw = (xgateStorage *)mem');
&remplace('./XGate/xgate.cpp', 'storage \* xgate::getProgramChunk', 'xgateStorage * xgate::getProgramChunk');
&remplace('./XGate/xgate.cpp', 'storage \* xgate::mem_getChunk', 'xgateStorage * xgate::mem_getChunk');
&remplace('./XGate/xgate.cpp', 'mem_XGMEMChunk = new rwStorage', 'mem_XGMEMChunk = new xgateStorage');
&remplace('./XGate/xgate.cpp', 'storage \*sto=getProgramChunk', 'xgateStorage *sto=getProgramChunk');
