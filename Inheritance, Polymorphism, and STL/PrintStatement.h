#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class PrintStatement: public Statement
{
private:
	std::string m_variableName;
	bool print_all_judge; 
	
public:
	PrintStatement(std::string variableName);
	PrintStatement(bool print_all_true);
	virtual ~PrintStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
