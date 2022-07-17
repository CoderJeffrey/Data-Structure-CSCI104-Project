// PrintStatement.cpp:
#include "PrintStatement.h"


PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}

PrintStatement::PrintStatement(bool print_all_validate)
	: print_all_judge(print_all_validate )
{}


PrintStatement::~PrintStatement()
{}

void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	//cout << "Get Into Execute As a PRINT" << endl;
	if(print_all_judge==true)
	{
		state->print_all_variable(outf);
	}
	else
	{
		state->print_variable(m_variableName,outf);
	}
}
