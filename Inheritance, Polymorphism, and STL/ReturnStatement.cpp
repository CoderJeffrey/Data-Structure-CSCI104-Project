#include "ReturnStatement.h"
#include "Statement.h"

using namespace std;

Return_Statement::Return_Statement()
{}

Return_Statement::~Return_Statement()
{}

void Return_Statement::execute(ProgramState* state, ostream &outf)
{
    state->Return_Statement();
}