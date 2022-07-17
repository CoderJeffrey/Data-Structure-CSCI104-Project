#include "GotoStatement.h"
#include <iostream>

using namespace std;

Goto::Goto(int line)
    : lineNumber(line)
{}

Goto::~Goto()
{}


void Goto::execute(ProgramState* state, ostream &outf)
{
    state->Go_to(lineNumber);
}
 