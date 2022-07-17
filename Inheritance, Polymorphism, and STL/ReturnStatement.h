#include "Statement.h"
#include "ProgramState.h"

class Return_Statement: public Statement
{
private:

public:
	Return_Statement();
	virtual ~Return_Statement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};