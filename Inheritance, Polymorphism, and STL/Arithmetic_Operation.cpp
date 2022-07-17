#include "Arithmetic_Operation.h"

#include <iostream>
#include <string>
using namespace std;


Arithmetic_Operation::Arithmetic_Operation(string operation, string variables_name, string val)
    :operation_type(operation), variables(variables_name), Second_parameter(val)
{}

Arithmetic_Operation::~Arithmetic_Operation()
{}

void Arithmetic_Operation::execute(ProgramState* state, ostream &outf)
{
    if(operation_type=="ADD")
    {
        state->add(variables,Second_parameter);
    }

    else if(operation_type=="SUB")
    {
        state->sub(variables,Second_parameter);   
    }

    else if(operation_type=="DIV")
    {
        state->divide(variables,Second_parameter);
    }

    else if(operation_type=="MULT")
    {
        state->mult(variables,Second_parameter);
    }
    
}