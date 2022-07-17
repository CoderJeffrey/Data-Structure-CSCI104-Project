#include "EndStatement.h"
#include <iostream>

using namespace std;
END_Statement::END_Statement(){}

void END_Statement::execute(ProgramState* state, ostream &outf)
{
    state->end_func();
}

END_Statement::~END_Statement(){}