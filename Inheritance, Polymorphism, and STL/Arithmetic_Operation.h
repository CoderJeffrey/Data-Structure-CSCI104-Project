
#include "Statement.h"
#include "ProgramState.h"


class Arithmetic_Operation:public Statement 
{
    public:
    Arithmetic_Operation(std::string operation, std::string variables_name, string val);
    virtual ~Arithmetic_Operation();
    virtual void execute(ProgramState* state, std::ostream &outf);

    private:
    std::string operation_type;
    std::string variables;
    std::string Second_parameter;
    int cal_value;

};