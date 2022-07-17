#include "IFStatement.h"
#include <iostream>

using namespace std;

IfThen::IfThen(string First, string Operator, int comparable, string _THEN_Keyword, int jump_to_line_number)
    :var(First),op(Operator),val(comparable),Then_Keyword(_THEN_Keyword),lineNumber(jump_to_line_number)
{}

IfThen::~IfThen()
{}

void IfThen::execute(ProgramState* state, ostream &outf)
{
    state->IF_Statement(var, op, val, Then_Keyword, lineNumber);
}