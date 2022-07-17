// LetStatement.cpp:
#include "LetStatement.h"

//JUSt for DEBUGGING
#include <iostream>
using namespace std;

LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{}

LetStatement::~LetStatement()
{}

// LetStatement::~LetStatement()
// {	
// 	delete this;
// }


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	//cout << "Get Into Execute As a LET" << endl;
	state->let(m_variableName,m_value);
}
