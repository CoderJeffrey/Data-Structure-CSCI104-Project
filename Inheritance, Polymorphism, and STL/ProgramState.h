// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.
#include <map>
#include <stack>

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

using namespace std;

class ProgramState
{
public:
	ProgramState(int numLines);

	//~ProgramState();
	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.

	//  like MULT ADD SUB DIV  GOTO GOSUB RETURN END . IF PRINT PRINTALL
	int get_counter();
	void let(string name, int value);

	//use ostream instead of only cout
	void print_variable(string name, ostream& outf);
	void print_all_variable(ostream& outf);

	void add(string Variable, int value);
	void add(string Variable, string value);

	void sub(string Variable, int value);
	void sub(string Variable, string value);
	
	void mult(string Variable, int value);
	void mult(string Variable, string value);
	
	void divide(string Variable, int value);
	void divide(string Variable, string value);
	
	void Go_to(int lineNumber);
	void IF_Statement(string First, string Operator, int comparable, string THEN, int jump_to_line_number);
	void Go_Sub(int lineNumber);
	void Return_Statement();
	
	void end_func();
	// void end_dot_statement();
 
 private:
	int m_numLines;
	int counter;
	map<string, int> values;
	stack<int> track_lines;
};

#endif
