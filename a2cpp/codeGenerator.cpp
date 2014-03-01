#include <cassert> //assert
#include <iostream>
#include <iomanip> //setioflags (setw)

#include "codeGenerator.h"
#include "automataConfiguration.h"
#include "automata.h"
#include <iomanip> //setioflags (setw)
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
	string modelName = m_configuration->modelName();

	CPP << "/** automata simulation" << endl;
	CPP << "automatically generated using a2cpp." << endl;
	CPP << "DO NOT MODIFY." << endl;
	CPP << " */" << endl << endl; 

	CPP << "#include <cassert> //assert" << endl;
	CPP << "#include \"" << m_prefix << ".h\"" << endl;
	CPP << "#include \"" << modelName << "_instruction.h\"" << endl;
	CPP << "#include \"" << modelName << "_core.h\"" << endl;
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
	outputH.beforeStream() << endl;
}

void codeGenerator::initHeader(fileHeaderGeneration &outputH)
{
	string modelName = m_configuration->modelName();

	notificationMasks(outputH);	
	externalResourcesOffsets(outputH);	
	outputH.beforeStream() << "class "<< modelName << "_instruction;" << endl;
	outputH.beforeStream() << "class core;" << endl << endl;
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
	const unsigned int nbBitsInstClasses = nbBitsToCodeValue(m_configuration->getNbInstructionClasses());
	const unsigned int conditionSizeInBits = nbBitsInstClasses+nbExtRes;
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
	outputH.publicStream() << "\t//\\param ic the instruction class code. " << endl;
	outputH.publicStream() << "\t//\tThis is the instruction class code of the next instruction that will enter inside pipeline. " << endl;
	outputH.publicStream() << "\t//\\return notifications (same order than in .config file)." << endl;
	outputH.publicStream() << "\tunsigned int execOneState(const unsigned int extResState, const unsigned int ic);" << endl;
	CPP << "//this function is the main function that should be called at each state." << endl;
	CPP << "//It returns notifications (same order than in .config file)." << endl;
	CPP << "unsigned int " << m_prefix << "::execOneState(const unsigned int extResState, const unsigned int ic) {" << endl;
	m_nbTab++;
	//const unsigned int externalResourcesSize = m_configuration -> getExternalResourcesStringVector().size();
	CPP << "const unsigned int conditionId = (extResState << " << dec << nbBitsInstClasses << ") | ic; " << endl;
	//ok. At this point, we got the hash code of conditionId. Then calculate the condition that is taken.
	CPP << "const nextType next = nextState_" << pipelineName << "[(m_currentState <<" <<dec<<conditionSizeInBits<<") + conditionId];"<< endl;
	CPP << "m_currentState = next & 0x"<< hex << (1<<stateSizeInBits)-1 <<";"<< dec << endl;
	CPP << "#ifdef PIPELINE_DEBUG" << endl;
	CPP << "\tassert(m_currentState < 532 && \"Target state does not exists\");" << endl;
	CPP << "#endif" << endl;
	CPP << "return (next >> "<< dec << stateSizeInBits <<");"<< dec << endl;
	m_nbTab--;
	CPP << "}" << endl;
	
}

void codeGenerator::function_init(fileHeaderGeneration &outputH)
{
	outputH.publicStream() << "\t//this function init internal data structures." << endl;
	outputH.privateStream() << "\tcore *m_core;" << endl;
	outputH.publicStream() << "\tvoid init(core *);" << endl;
	CPP << "void " << m_prefix << "::init(core *_core) {" << endl;
	CPP << "\tm_core = _core;" << endl;
	CPP << "\tm_currentState = 0;" << endl;
	CPP << "}" << endl;

}

void codeGenerator::tabular_nextState(fileHeaderGeneration &outputH)
{
	string pipelineName = m_configuration->getPipelineName();	
	automata *aut = m_configuration->getAutomata();	
	const unsigned int nbExtRes = m_configuration->getNbExternalResources();
	const unsigned int nbBitsInstClasses = nbBitsToCodeValue(m_configuration->getNbInstructionClasses());
	const unsigned int conditionSizeInBits = nbBitsInstClasses+nbExtRes;
	const unsigned int nbConditions = (1<<conditionSizeInBits);
	const unsigned int nbStates = aut->getNbStates();
	const unsigned int stateSizeInBits = nbBitsToCodeValue(nbStates);
	const unsigned int tabSize = nbConditions*nbStates;
	const unsigned int nbNotifications = m_configuration->getNbNotifications();
	const unsigned int nbBitsToCodeAState = aut->getNbBitsToCodeAState();
	const unsigned int nbBitsToCodeATransition = aut->getNbBitsToCodeATransition();
	assert(nbBitsToCodeATransition == nbNotifications+conditionSizeInBits);
	CPP << "// next state tabular" << endl;
	CPP << "// a condition id is the concatenation of" << endl;
	CPP << "// * the class id of the next instruction to fetch (" << nbBitsInstClasses << " low bits)" << endl;
	CPP << "// * external ressource states (" << nbExtRes << " high bits)" << endl;
	CPP << "// The condition id size is in bits : " << conditionSizeInBits << endl;
	CPP << "// there are " << nbStates << " states" << endl;
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
	CPP << "//       and the notifications to do (highest bits)" << endl;

	//define nextType:
	unsigned int nextTypeSize = stateSizeInBits + nbNotifications;
	if(nextTypeSize < 33) outputH.beforeStream() << "typedef unsigned int nextType;" << endl;
	else if(nextTypeSize < 65) outputH.beforeStream() << "typedef unsigned long long nextType;" << endl;
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
	const unsigned int nbBitsTab = stateSizeInBits+nbNotifications;
	const unsigned int nbBytesTab = (nbBitsTab & 0x3) ? (nbBitsTab>>2)+1 : (nbBitsTab>>2);
	//start.
	for(unsigned int state = 0; state < nbStates; state++)
	{

		int stateId = aut->getA2AStateFromA2CPP(state);
		C_BDD currentSource = C_BDD::varCompareConst (0, nbBitsToCodeAState, C_BDD::kEqual, stateId) ;
		C_BDD automataFromCurrentSources = aut->bdd() & currentSource;
		if(state) m_cpp << ", ";
		m_cpp << endl;
		CPP; //tabs
		for(unsigned int cond = 0; cond < nbConditions; cond++)
		{
			//correct ouput format..
			if(cond) m_cpp << ", ";
			//restrict BDD to the condition
			C_BDD currentCond = C_BDD::varCompareConst (nbBitsToCodeAState+nbNotifications, conditionSizeInBits , C_BDD::kEqual, cond) ;
			C_BDD automataFromCurrentSourcesAndCondition = automataFromCurrentSources & currentCond;

			//get the target from that.
			PMUInt64 targetId = 0;
			C_BDD currentTargets = automataFromCurrentSourcesAndCondition.bddByRightShifting(nbBitsToCodeAState+nbBitsToCodeATransition);
			TC_UniqueArray <PMUInt64> currentTargetsArray;
			currentTargets.buildValue64Array(currentTargetsArray, nbBitsToCodeAState);
			assert(currentTargetsArray.count() <= 1);
			for (PMSInt32 j=0 ; j<currentTargetsArray.count () ; j++) //max 1 loop.
				targetId = currentTargetsArray(j COMMA_HERE);
			int targetA2CPP = aut->getA2CPPStateIdFromA2A(targetId);

			//get the notification.
			PMUInt64 notificationId = 0;
			C_BDD currentNotification = automataFromCurrentSourcesAndCondition.bddByRightShifting(nbBitsToCodeAState);
			currentNotification = currentNotification.existsOnBitsAfterNumber(nbNotifications);
			TC_UniqueArray <PMUInt64> currentNotificationsArray;			
			currentNotification.buildValue64Array(currentNotificationsArray, nbNotifications);			
			assert(currentNotificationsArray.count() <= 1);
			for (PMSInt32 j=0 ; j<currentNotificationsArray.count () ; j++) //max 1 loop.
				notificationId = currentNotificationsArray(j COMMA_HERE);
			assert(notificationId < (1UL<<nbNotifications));

			//concatenate the whole.
			PMUInt64 val = notificationId << stateSizeInBits |  targetA2CPP;
			//and print.
			m_cpp << "0x" << hex << setfill('0') << setw(nbBytesTab) << val;
		}
		
	}
	m_cpp << endl;
	m_nbTab--;
	CPP << "};" << endl;
}
