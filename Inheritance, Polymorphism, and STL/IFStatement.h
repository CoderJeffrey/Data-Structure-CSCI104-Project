#include "Statement.h"
#include "ProgramState.h"

using namespace std;

class IfThen: public Statement
{
    public:
    IfThen(string First, string Operator, int comparable, string THEN_Keyword, int jump_to_line_number);
    virtual ~IfThen();
    virtual void execute(ProgramState* state, ostream &outf);

    private:
	string var;
	string op;
	int val;
	string Then_Keyword;
    int lineNumber;
};