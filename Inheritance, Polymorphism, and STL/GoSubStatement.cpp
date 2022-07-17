#include "GoSubStatement.h"

using namespace std;

GoSubStatement::GoSubStatement(int line_num)
    : lineNumber(line_num)
{}

GoSubStatement::~GoSubStatement(){}

void GoSubStatement::execute(ProgramState* state, ostream &outf)
{
    state->Go_Sub(lineNumber);
}