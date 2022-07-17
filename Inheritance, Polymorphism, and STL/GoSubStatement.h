
#include "ProgramState.h"
#include "Statement.h"

using namespace std;

class GoSubStatement : public Statement
{
private:
    int lineNumber;
public:
    GoSubStatement(int line_num);
    virtual ~GoSubStatement();
    virtual void execute(ProgramState* state, ostream &outf);
};



