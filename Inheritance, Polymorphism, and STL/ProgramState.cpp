#include "ProgramState.h"

#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <math.h>

using namespace std;


ProgramState::ProgramState(int value_line)
{
    this->counter = 1;
    this->m_numLines = value_line;
}

// ProgramState::~ProgramState()
// {
//     delete this;
// }

void ProgramState::let(string name, int value)
{
    map<string,int>::iterator it;
    it = values.find(name);
    if(it!=values.end())
    {
       it->second=value; 
    }

    else
    {
        values.emplace(name,value);
    }

    counter++;
    return;
}

void ProgramState::print_variable(string name, ostream& outf)
{
    outf << this->values[name] << endl;
    counter++;
}

void ProgramState::print_all_variable(ostream& outf)
{
    map<string,int>::iterator itr;
    for(itr = values.begin(); itr != values.end();++itr)
    {
        outf << itr->first << " " << itr->second <<endl;
    }
    counter++;
}

int ProgramState::get_counter()
{
    return this->counter;
}

/*
    void add(string Variable, int value);
	void sub(string Variable, int value);
	void mult(string Variable, int value);
	void divide(string Variable, int value);
*/


void ProgramState::add(string variable, string second)
{
    map<string, int>::iterator itr; 
    itr = values.find(variable);

    int value_for_second;
    map<string, int>::iterator itr2; 
    itr2 = values.find(second);
    if(itr2 != values.end()) value_for_second = itr2->second;
    else value_for_second = stoi(second);

    if(itr != values.end())
    {
        itr->second = itr->second + value_for_second;
    }

    //Edge Case-The variable was not created before, as a result, its default value is 0
    // 0 + any number = any number
    else
    {
        itr->second = value_for_second;
    }
    
    counter++;
}



void ProgramState::sub(string variable, string second)
{
    map<string, int>::iterator itr; 
    itr = values.find(variable);

    int value_for_second;
    map<string, int>::iterator itr2; 
    itr2 = values.find(second);
    if(itr2 != values.end()) value_for_second = itr2->second;
    else value_for_second = stoi(second);

    if(itr != values.end())
    {
        itr->second = itr->second - value_for_second;
    }

    //Edge Case-The variable was not created before, as a result, its default value is 0
    // 0 - any number = (-1) * any number
    else
    {
        itr->second = value_for_second * (-1);
    }

    counter++;
}




void ProgramState::mult(string variable, string second)
{
    map<string, int>::iterator itr; 
    itr = values.find(variable);

    int value_for_second;
    map<string, int>::iterator itr2; 
    itr2 = values.find(second);
    if(itr2 != values.end()) value_for_second = itr2->second;
    else value_for_second = stoi(second);

    if(itr != values.end())
    {
        itr->second = itr->second * value_for_second;
    }

    //Edge Case-The variable was not created before, as a result, its default value is 0
    // 0 * any number = 0
    else
    {
        itr->second = 0;
    }

    counter++;
}





void ProgramState::divide(string variable, string second)
{
    //exception needed
    int value_for_second;
    map<string, int>::iterator itr2; 
    itr2 = values.find(second);
    if(itr2 != values.end()) value_for_second = itr2->second;
    else value_for_second = stoi(second);

    if(value_for_second==0)
    {
        end_func();
        throw runtime_error("Divide by zero exception");
        return;
    }

    map<string, int>::iterator itr; 
    itr = values.find(variable);
    if(itr != values.end())
    {
        itr->second = (int)floor(((double)itr->second / (double)value_for_second));  
    }

    //Edge Case-The variable was not created before, as a result, its default value is 0
    // 0 / any number = 0 (except 0)
    else
    {
        itr->second = 0;
    }
    counter++;
}


//Arithmetic Parts -- ABOVE

// END Statement 
void ProgramState::end_func()
{
    counter = 0;
    return;
}

//Goto & IF THEN Statement

void ProgramState::Go_to(int lineNumber)
{
    counter = lineNumber;
    if(lineNumber < 0 || lineNumber > m_numLines)
    {
        throw logic_error("Out of Range");
    }
}

void ProgramState::IF_Statement(string First, string Operator, int comparable, string THEN_Keyword, int jump_to_line_number)
{
    //Edge Case: Then was missing
    // if(THEN_Keyword!="Then")
    // {
    //     cout << "Missing 'Then' KeyWord" << endl;
    //     return;
    // }

    map<string,int>::iterator itr;
    itr = values.find(First);
    int first_value = itr->second;

    bool final_result;
    // <, <=, >, >=, = (equal to), or <> (not equal to).
    if(Operator=="<")
    {
        if(first_value < comparable) final_result = true;
        else final_result = false;
    }
    else if(Operator=="<=")
    {
        if(first_value <= comparable) final_result = true;
        else final_result = false;
    }
    else if(Operator==">")
    {
        if(first_value > comparable) final_result = true;
        else final_result = false;
    }
    else if(Operator==">=")
    {
        if(first_value >= comparable) final_result = true;
        else final_result = false;
    }
    else if(Operator=="=")
    {
        if(first_value == comparable) final_result = true;
        else final_result = false;
    }
    else if(Operator=="<>")
    {
        if(first_value != comparable) final_result = true;
        else final_result = false;
    }

    if(final_result==true)
    {
        Go_to(jump_to_line_number);
    }

}

//GoSub Statement

void ProgramState::Go_Sub(int lineNum)
{
    //stack<int> track_lines;
    track_lines.push(counter);
    Go_to(lineNum);
}

void ProgramState::Return_Statement()
{
    int last_line_num = 0;
    last_line_num = track_lines.top();
    track_lines.pop();
    //GO to next line of last_line_num
    last_line_num++;
    Go_to(last_line_num);
}