#include "Statement.h"
#include "ProgramState.h"

using namespace std;

class END_Statement: public Statement
{
    private:

    public:
    END_Statement();
    virtual ~END_Statement();
    virtual void execute(ProgramState* state, ostream &outf);
};