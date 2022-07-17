// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"

#include "Arithmetic_Operation.h"
#include "EndStatement.h"
#include "GotoStatement.h"
#include "IFStatement.h"
#include "GoSubStatement.h"
#include "ReturnStatement.h"

//other .h file
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}


//Get the line for all the Instructions
void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	string line;
	while(!inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}

//Get the Instructions for all the line
Statement * parseLine(string line)
{
	int start_line_number_key;
	Statement * statement;	
	stringstream ss;
	string type;
	string arith_variable;
	string var;
	string op;
	int val;

	string Then_Keyword;
	int lineNumber;

	ss << line;
	ss >> start_line_number_key;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}

	// Incomplete;  TODO:  Finish this function!

	//PRINTSTATEMENT: PRINT_VARIABLE + PRINT_ALL
	if ( type == "PRINT" )
	{
		ss >> var;
		statement = new PrintStatement(var);
	}

	if ( type == "PRINTALL")
	{
		bool print_all_true = true;
		statement = new PrintStatement(print_all_true);
	}

	//Arithmetic Parts - Add /
 	if ( type == "ADD")
	{
		ss >> var;
		ss >> arith_variable;
		statement = new Arithmetic_Operation("ADD",var,arith_variable);
	}

	if ( type == "SUB")
	{
		ss >> var;
		ss >> arith_variable;
		statement = new Arithmetic_Operation("SUB",var,arith_variable);
	}

	if ( type == "MULT")
	{
		ss >> var;
		ss >> arith_variable;
		statement = new Arithmetic_Operation("MULT",var,arith_variable);
	}

	if ( type == "DIV")
	{
		ss >> var;
		ss >> arith_variable;
		statement = new Arithmetic_Operation("DIV",var,arith_variable);
	}

	//Arithmetic Part ends

	if ( type == "END" || type == ".")
	{
		statement = new END_Statement();
	}

	//Goto Statement && IF THEN Statement

	if(type == "GOTO")
	{
		ss >> val;
		statement = new Goto(val);
	}

	if(type == "IF")
	{
		ss >> var;
		ss >> op;
		ss >> val;
		ss >> Then_Keyword;
		ss >> lineNumber;
		statement = new IfThen(var,op,val,Then_Keyword,lineNumber);
	}

	//GOSUB and Return Statement 
	if(type == "GOSUB")
	{
		ss >> val;
		statement = new GoSubStatement(val);
	}

	if(type == "RETURN")
	{
		statement = new Return_Statement();
	}

	return statement;
}

void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );     
	// Incomplete;  TODO:  Finish this function!
	ProgramState* pstester = new ProgramState(program.size());

	//Erro-Handling
	try{
		while(program[pstester->get_counter()]!=nullptr)
		{
			//cout << pstester->get_counter() << " Times" << endl;
			program.at(pstester->get_counter())->execute(pstester, outf);
		}
	}

	catch(logic_error &e)
	{
		outf<<e.what()<<endl;
	}
	
	catch(exception &e){
		outf << e.what() <<endl;
	}

	for(int i=1;i<program.size();i++)
	{
		delete program[i];
	}
	
	delete pstester;
}
