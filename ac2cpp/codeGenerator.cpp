#include <cassert> //assert
#include <iostream>
#include <iomanip> //setioflags (setw)

#include "codeGenerator.h"
#include "automataConfiguration.h"
#include "automata.h"
#include <iomanip> //setioflags (setw)
#include <math.h>
using namespace std;


#define CPP m_cpp << tab() 

extern bool verbose;

codeGenerator::codeGenerator(automataConfiguration *configuration) : 
	m_nbTab(0),
	m_configuration(configuration)
{
}

string codeGenerator::tab()
{
	string t;
	for(unsigned int i=0;i<m_nbTab ; i++) t += "\t";
	return t;
}

void codeGenerator::generateFilePreamble()
{
	CPP << "/** automata simulation" << endl;
	CPP << "automatically generated using ac2cpp." << endl;
	CPP << "DO NOT MODIFY." << endl;
	CPP << " */" << endl << endl; 

	CPP << "#include <cassert> //assert" << endl;
	CPP << "#include \"" << m_prefix << ".h\"" << endl;
	CPP << "#include \"instruction.h\"" << endl;
	CPP << "#include \"arch.h\"" << endl;
	CPP << endl;
}

void codeGenerator::externalResourcesOffsets(fileHeaderGeneration &outputH)
{
	const int size = m_configuration->getNbExternalResources();
	outputH.beforeStream() << "//These offsets should be used to determine the state of external resources" << endl;
	for(int i=0;i<size; i++)
	{
		string extName = "ext_res_"+m_configuration->getExternalResourcesStringVector()[i];
		stoupper(extName);
		outputH.beforeStream() << "#define " << setw(30) << left << extName << " "
			                   << dec << i << endl;
	}
	outputH.beforeStream() << endl;
}

void codeGenerator::notificationMasks(fileHeaderGeneration &outputH)
{
	const int size = m_configuration->getNbNotifications();
	int mask = 1;
	outputH.beforeStream() << "//These masks should be used to access a specific notification" << endl;
	for(int i=0;i<size; i++)
	{
		string symbol = m_configuration->getNotificationString(i)+"_Mask";
		stoupper(symbol); //uppercase.
		outputH.beforeStream() << "#define " << setw(30) << left << symbol << " "
			                   << hex << showbase << mask << endl;
		mask <<= 1;
	}
	//TODO: Finir.
	automata *aut = m_configuration->getAutomata();	
	const unsigned int nbBitsInst = aut->getNbBitsToCodeATransition()-m_configuration->getNbExternalResources()-m_configuration->getNbNotifications();
	const unsigned int nbBitsToCodeATransitionWithoutResExt = aut->getNbBitsToCodeATransition()-m_configuration->getNbExternalResources();
	outputH.beforeStream() << "#define " << setw(31) << left << "INST_MASK " << hex << showbase << (1UL<<nbBitsInst)-1 << endl;
	outputH.beforeStream() << endl;
}

void codeGenerator::initHeader(fileHeaderGeneration &outputH)
{
	string modelName = m_configuration->modelName();

	notificationMasks(outputH);	
	externalResourcesOffsets(outputH);	
	outputH.beforeStream() << "class "<< modelName << "_instruction;" << endl;
	outputH.beforeStream() << "class arch;" << endl << endl;
}

void codeGenerator::initCPPFile(std::string filename)
{
	m_nbTab = 0;	
	m_cpp.open(filename.c_str(), ofstream::out);
	generateFilePreamble();
	if(verbose) cout << "generate C++ file \"" << filename << "\"..";
}

void codeGenerator::closeCPPFile()
{
	m_cpp << endl; //be sure file ends with endl.
	m_cpp.close();
	if(verbose) cout << endl;
}

void codeGenerator::generateWithPrefix(std::string prefix, fileHeaderGeneration &fileHeader)
{
	m_prefix = prefix;
	initHeader(fileHeader);

	initCPPFile(prefix+".cpp");
	function_execOneState(fileHeader);
	function_init(fileHeader);
	closeCPPFile();

	initCPPFile(prefix+"-1.cpp");
	tabular_nextState(fileHeader);
	closeCPPFile();
}

void codeGenerator::function_execOneState(fileHeaderGeneration &outputH)
{
	automata *aut = m_configuration->getAutomata();	
	//const unsigned int conditionSizeInBits = aut->getNbBitsToCodeATransition();
	const unsigned int nbExtRes = m_configuration->getNbExternalResources();
	const unsigned int nbBitsInst = aut->getNbBitsToCodeATransition()-nbExtRes-m_configuration->getNbNotifications();//nbBitsToCodeValue(m_configuration->getNbInstruction());
	const unsigned int nbStates = aut->getNbStates();
	const unsigned int stateSizeInBits = nbBitsToCodeValue(nbStates);
	string pipelineName = m_configuration->getPipelineName();

	outputH.privateStream() << "\t//store the current state id." << endl;
	outputH.privateStream() << "\tunsigned int m_currentState;" << endl;
	outputH.publicStream() << "\t//this function is the main function that should be called at each state." << endl;
	outputH.publicStream() << "\t//\\param extResState The external resources states. " << endl;
	outputH.publicStream() << "\t//\t0=>resource is free, 1=>resource is taken. " << endl;
	outputH.publicStream() << "\t//\tOne bit for each resource. The order of resources is the same as in the .config file:" << endl;
	outputH.publicStream() << "\t//\tthe first external resource defined is the lowest significant bit" << endl;
	outputH.publicStream() << "\t//\\return notifications (same order than in .config file)." << endl;
	outputH.publicStream() << "\tunsigned long int execOneState(const unsigned int extResState);" << endl;
	CPP << "//this function is the main function that should be called at each state." << endl;
	CPP << "//It returns notifications (same order than in .config file)." << endl;
	CPP << "unsigned long int " << m_prefix << "::execOneState(const unsigned int extResState) {" << endl;
	m_nbTab++;
	//const unsigned int externalResourcesSize = m_configuration -> getExternalResourcesStringVector().size();
	//Old instruction
	//CPP << "const unsigned int conditionId = (extResState << " << dec << nbBitsInst << ") | ic; " << endl;
	//ok. At this point, we got the hash code of conditionId. Then calculate the condition that is taken.
	CPP << "const nextType next = nextState_" << pipelineName << "[(m_currentState <<" <<dec<<nbExtRes<<") + extResState];"<< endl;
	CPP << "if(next==-1) {" << endl << "std::cerr << \"Final state!\" << std::endl;" << endl << "}" << endl;
	CPP << "//std::cerr << std::hex << m_currentState << \" -> \";" << endl;
	CPP << "m_currentState = next & 0x"<< hex << (1<<stateSizeInBits)-1 <<";"<< dec << endl;
	CPP << "//std::cerr << std::hex << m_currentState << std::endl;" << endl;
	CPP << "#ifdef PIPELINE_DEBUG" << endl;
	// TODO: don't understand this assert. -> in fact it is the maximal number of states
	CPP << "\tassert(m_currentState < 532 && \"Target state does not exists\");" << endl;
	CPP << "#endif" << endl;
	CPP << "return (next >> "<< dec << stateSizeInBits <<");"<< dec << endl;
	m_nbTab--;
	CPP << "}" << endl;
	
}

void codeGenerator::function_init(fileHeaderGeneration &outputH)
{
	outputH.publicStream() << "\t//this function init internal data structures." << endl;
	outputH.privateStream() << "\tarch *m_arch;" << endl;
	outputH.publicStream() << "\tvoid init(arch *);" << endl;
	CPP << "void " << m_prefix << "::init(arch *_arch) {" << endl;
	CPP << "\tm_arch = _arch;" << endl;
	CPP << "\tm_currentState = 0;" << endl;
	CPP << "}" << endl;

}

void codeGenerator::tabular_nextState(fileHeaderGeneration &outputH)
{
	string pipelineName = m_configuration->getPipelineName();	
	automata *aut = m_configuration->getAutomata();	
	const unsigned int nbExtRes = m_configuration->getNbExternalResources();
	const unsigned int nbBitsInst = aut->getNbBitsToCodeATransition()-nbExtRes-m_configuration->getNbNotifications();//nbBitsToCodeValue(m_configuration->getNbInstruction());
	const unsigned int nbConditions = (1<<nbExtRes)-1;
	const unsigned int nbStates = aut->getNbStates();
	const unsigned int stateSizeInBits = nbBitsToCodeValue(nbStates);
	const unsigned int tabSize = ((nbStates) << nbExtRes) | ((1 << nbExtRes) -1);//nbConditions*nbStates;
	const unsigned int nbNotifications = m_configuration->getNbNotifications();
	const unsigned int nbBitsToCodeAState = aut->getNbBitsToCodeAState();
	const unsigned int nbBitsToCodeATransition = aut->getNbBitsToCodeATransition();
	assert(nbBitsToCodeATransition == nbNotifications+nbExtRes+nbBitsInst);
	CPP << "// next state tabular" << endl;
	CPP << "// a condition id is" << endl;
	CPP << "// * external ressource states (" << nbExtRes << " bits)" << endl;
	CPP << "// there are " << nbStates << " states and so " << stateSizeInBits << " bits" << endl;
	CPP << "// The index of tabular is coded on " << stateSizeInBits + nbExtRes << " bits" << endl;
	CPP << "// Tabular ("<<tabSize<<" entries) works like this:" << endl;
	CPP << "//"<< endl;
	CPP << "//                    current condition" << endl;
	CPP << "//                         |" << endl;
	CPP << "//                        \\_/" << endl;
	CPP << "//                 –––––––––––––" << endl;
	CPP << "//                 |  |  |  |  |    " << endl;
	CPP << "// source state -> |  |  |XX|  | => XX " << endl;
	CPP << "//                  ...." << endl;
	CPP << "// => XX is the concatenation of the next state (low "<<stateSizeInBits<<" bits) " << endl;
	CPP << "//       and the notifications to do (" << nbNotifications << " middle bits)" << endl;
	CPP << "//       and the pc coming in the pipeline (" << nbBitsInst << " highest bits)" << endl;

	//define nextType:
	unsigned int nextTypeSize = stateSizeInBits + nbNotifications + nbBitsInst;
	if(nextTypeSize < 33) outputH.beforeStream() << "typedef unsigned int nextType;" << endl;
	else if(nextTypeSize < 65) outputH.beforeStream() << "typedef unsigned long long nextType;" << endl;
	// Cette condition me cause beaucoup de problème.
	else {
		cerr << "Too big automata. more than 64 bits are required to encode a state and a notification : " ;
		cerr << stateSizeInBits << " bits for a state and ";
		cerr << nbNotifications << " notifications." << endl;
	}
	//header declaration.
	outputH.beforeStream() << "//tabular that give the next state (using current state, and condition)" << endl;
	outputH.beforeStream() << "extern const nextType nextState_"<< pipelineName << "["<<dec<<tabSize<<"];" << endl;
	
	//CPP generation.
	CPP << "const nextType nextState_" << pipelineName << "["<<dec<<tabSize<<"] = {";
	m_nbTab++;
	//nbBits to encode one value in the table.
	const unsigned int nbBitsTab = stateSizeInBits+nbNotifications+nbBitsInst;
	const unsigned int nbBytesTab = (nbBitsTab & 0x3) ? (nbBitsTab>>2)+1 : (nbBitsTab>>2);
	//start.
	for(int i = 0; i < tabSize ; i++) {
		m_cpp << endl;
		m_cpp << "0x" << hex << aut->getAC2CPPStateIdFromAC2AC(i) << ",";
	}
	m_cpp << endl;
	m_nbTab--;
	CPP << "};" << endl;
}
