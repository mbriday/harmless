/** 
 * p2a
 *
 * p2a is copyright (c) IRCCyN 2005+
 * p2a est protege par la loi sur la propriete intellectuelle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 * $Id$
 */

#include <iostream>
#include <string.h>

#include "systemConfiguration.h"

#include "automata.h"
#include "pipeline.h"

#include "systemState.h" //debug.
#include "time/C_Timer.h"
#include "strings/C_String.h"
#include "streams/C_ConsoleOut.h"
#include "command_line_interface/F_mainForLIBPM.h"

using namespace std;

string configFilename;
string outputFilename;
string graphvizFilename;
//cause p2a to be verbose: showing septs of data generation.
bool verbose;

static void print_help()
{
	cout << "p2a is copyright (c) IRCCyN 2005+" << endl;
	cout << "p2a est protege par la loi sur la propriete intellectuelle" << endl;
	cout <<  endl;
	cout << "This program is free software; you can redistribute it and/or modify" << endl;
	cout << "it under the terms of the GNU General Public License as published by" << endl;
	cout << "the Free Software Foundation; either version 2 of the License, or" << endl;
	cout << "(at your option) any later version." << endl;
	cout << endl;
	cout << "Usage: p2a [options] file" << endl;
	cout << "The file is the configuration file." << endl;
	cout << "Options:" << endl;
	cout << "--help\t\tthis help" << endl;
	cout << "--output|-o file\toutput file (.a2a)." << endl;
	cout << "--graphviz|-gv file\texport file in GraphViz format (.dot)." << endl;
	cout << "--verbose|-v \tcause p2a to be verbose: showing septs of data generation (to stderr)" << endl;
	cout << "--info-bdd|-i \tcause p2a to display the BDD package information messages" << endl;
	cout << "--max-ram-size=n|-m=n \tcause p2a to constraint the BDD memory usage < n MB" << endl;
	cout << "--max-and-cache-size=n|-a=n \tcause p2a to constraint the BDD AND cache map size to < 2**n" << endl;
	cout << "--max-ops-cache-size=n|-b=n \tcause p2a to constraint the BDD single operand operation cache map size to < 2**n" << endl;
	cout << "--max-hash-map-size=n|-c=n \tcause p2a to constraint the BDD hash map size to < 2**n" << endl;
}

static bool argumentWithInteger (const char * inArgument,
                                 const char * inString1,
                                 const char * inString2,
                                 PMUInt32 & outValue) {
	bool ok = strncmp (inArgument, inString1, strlen (inString1)) == 0 ;
  if (ok) {
    sscanf (& inArgument[strlen (inString1)], "%u", & outValue) ;
  }else{
	  ok = strncmp (inArgument, inString2, strlen (inString2)) == 0 ;
    if (ok) {
      sscanf (& inArgument [strlen (inString2)], "%u", & outValue) ;
    }
  }
  return ok ;
}

//check for arguments.
static bool parseArgumentList(int argc, const char *argv[])
{
  PMUInt32 value = 0 ;
	int i = 1; //remove program name.
	bool endRequest = false;
	while(i < argc)
	{
		if((!strncmp(argv[i],"--help",6)) || 
				  (!strncmp(argv[i],"-h",2)))
		{
			//help
			print_help();
			endRequest = true;
			i = argc; //end of argument process.
		} else if((!strncmp(argv[i],"--verbose",9)) || 
				  (!strncmp(argv[i],"-v",2)))
		{
			//verbose
			verbose = true;
			i++;
		}else if((!strncmp(argv[i],"--info-bdd",10)) || (!strncmp(argv[i],"-i",2))) {
			C_BDD::setDisplaysInformationMessages (true) ;
			i++;
		}else if (argumentWithInteger (argv[i], "--max-ram-size=", "-m=", value)) {
      C_BDD::setMaximumMemoryUsage (value) ;
			i++;
		}else if (argumentWithInteger (argv[i], "--max-and-cache-size=", "-a=", value)) {
      C_BDD::setANDOperationCacheMaxSize (value) ;
			i++;
		}else if (argumentWithInteger (argv[i], "--max-ops-cache-size=", "-b=", value)) {
      C_BDD::setSingleOperandOperationCacheMaxSize (value) ;
			i++;
		}else if (argumentWithInteger (argv[i], "--max-hash-map-size=", "-c=", value)) {
      C_BDD::setHashMapMaxSize (value) ;
			i++;
		} else if((!strncmp(argv[i],"--output",8)) || 
				  (!strncmp(argv[i],"-o",2)))
		{
			//output file
			if((i+1) < argc) outputFilename = argv[i+1];
			i+=2;
		} else if((!strncmp(argv[i],"--graphviz",10)) || 
				  (!strncmp(argv[i],"-gv",3)))
		{
			//graphviz file
			if((i+1) < argc) graphvizFilename = argv[i+1];
			i+=2;
		} else
		{
			//the filename is the config file.
			configFilename = argv[i];
			i++;
		}
	}
	return endRequest;
}

int mainForLIBPM (int argc, const char * argv[])
{
	verbose = false;
	if(!parseArgumentList(argc, argv))
	{
		if(configFilename.empty()) 
		{
			cerr << "error: configuration file!" << endl;
			print_help();
		} else {
			systemConfiguration config;	
			if(!config.load(configFilename)) return 1;
			
			pipeline * pipe = config.getPipeline();
			
			automata *autom = NULL ;
			macroMyNew (autom, automata(pipe));
			if(verbose) autom->printInternalConstants();
			if(verbose) cerr << endl << "Computing automata transitions... " << flush;
			C_Timer timer ;
			autom->computeAutomata();
			if(verbose) co << cStringWithUnsigned (autom->transitionCount ()) << " transitions ("<< timer << ")\n" ;
			autom->translateTransitionArrayIntoBDD (verbose) ;
			if(verbose) autom->printInternalStats();
			
			if(!graphvizFilename.empty()) autom->exportGraphViz(graphvizFilename);
			//save BEFORE minimization at this date..
			//if(!outputFilename.empty())   autom->save(outputFilename, config.modelName());

			autom->minimize(verbose);
			string mini = "Min"+graphvizFilename;
			if(!graphvizFilename.empty()) autom->exportGraphViz(mini);
			if(verbose) autom->printInternalStats();

			//save AFTER minimization ..
			if(!outputFilename.empty())   autom->save(outputFilename, config.modelName());

			macroMyDelete (autom) ;
      if (verbose) {
        C_BDD::printBDDpackageOperationsSummary (co) ;
      }
		}
	}
	return 0;
}
