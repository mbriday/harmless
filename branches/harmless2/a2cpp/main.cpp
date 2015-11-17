/** 
 * a2cpp
 *
 * a2cpp is copyright (c) IRCCyN 2005+
 * a2cpp est protege par la loi sur la propriete intellectuelle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * $Date: 2006-02-07 16:37:47 +0100 (Tue, 07 Feb 2006) $
 * $Rev: 6 $
 * $Author: mik $
 * $URL: https://a2cpp.rts-software.org/svn/main.cpp $
 * $Id: main.cpp 6 2006-02-07 15:37:47Z mik $
 */

#include <iostream>
#include <string.h>

#include "automataConfiguration.h"
#include "command_line_interface/F_mainForLIBPM.h"
#include "command_line_interface/C_BoolCommandLineOption.h"
#include "command_line_interface/F_Analyze_CLI_Options.h"
#include "strings/C_String.h"

//#include "fileHeaderGeneration.h"
//#include "generateState.h"

using namespace std;
bool verbose;


//string outputPrefixFilename;

C_BoolCommandLineOption gVerboseOption ("generic_cli_options",
                                        "display_help",
                                        'v',
                                        "verbose",
                                        "Display verbose information") ;

static void print_tool_help_message ()
{
	cout << "a2cpp is copyright (c) IRCCyN 2005+" << endl;
	cout << "a2cpp est protege par la loi sur la propriete intellectuelle" << endl;
	cout <<  endl;
	cout << "This program is free software; you can redistribute it and/or modify" << endl;
	cout << "it under the terms of the GNU General Public License as published by" << endl;
	cout << "the Free Software Foundation; either version 2 of the License, or" << endl;
	cout << "(at your option) any later version." << endl;
	cout << endl;
}

//---------------------------------------------------------------------------*

static const char * kSourceFileExtensions [] = {
  "a2a",
  NULL
} ;    

//---------------------------------------------------------------------------*

static const char * kSourceFileHelpMessages [] = {
  "an a2cpp automata",
  NULL
} ;    

//---------------------------------------------------------------------------*

//check for arguments.
/*bool parseArgumentList(int argc, const char *argv[], string &configFilename)
{
	
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
			
		} else
		{
			//the filename is the config file.
			configFilename = argv[i];
			i++;
		}
	}
	return endRequest;
}*/

//---------------------------------------------------------------------------*

const char * galgasVersionString (void) {
  return "3.1.3" ;
}

//---------------------------------------------------------------------------*

const char * projectVersionString (void) {
  return "?" ;
}

//---------------------------------------------------------------------------*

#include "codeGenerator.h"

int mainForLIBPM (int inArgc, const char * inArgv [])
{
//--- Analyze Command Line Options
  TC_UniqueArray <C_String> sourceFilesArray ;
  F_Analyze_CLI_Options (inArgc, inArgv,
                         sourceFilesArray,
                         kSourceFileExtensions,
                         kSourceFileHelpMessages,
                         print_tool_help_message) ;
  verbose = gVerboseOption.mValue ;
	automataConfiguration config;
	string configFilename;
	bool loadOk = false;
	if(sourceFilesArray.count () == 0) {
		loadOk = config.load ("");
	}else if(sourceFilesArray.count () == 1) {
		loadOk = config.load (sourceFilesArray (0 COMMA_HERE).cString (HERE));
	}
	if(loadOk)
	{
		string prefix = config.getPipelineName();
		codeGenerator cg(&config);
		fileHeaderGeneration fileHeader(prefix);
		cg.generateWithPrefix(prefix, fileHeader);
	} else {
		cerr << "error configuration file." << endl;
		print_tool_help_message();
	}
	return 0;
}

//---------------------------------------------------------------------------*

/*int mainForLIBPM (int argc, const char * argv[])
{
	automataConfiguration config;
	string configFilename;
	bool loadOk = false;
	if(!parseArgumentList(argc, argv, configFilename))
	{
		loadOk = config.load(configFilename);
	}
	if(loadOk)
	{
		string prefix = config.getPipelineName();
		codeGenerator cg(&config);
		fileHeaderGeneration fileHeader(prefix);
		cg.generateWithPrefix(prefix, fileHeader);
	} else {
		cerr << "error configuration file." << endl;
		print_help();
	}
	return 0;
}*/
