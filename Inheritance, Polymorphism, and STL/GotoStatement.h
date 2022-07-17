#include "Statement.h"
#include "ProgramState.h"

using namespace std;

class Goto: public Statement
{
    public:
    Goto(int line);
    virtual ~Goto();
    virtual void execute(ProgramState* state, ostream &outf);

    private:
    int lineNumber;
};