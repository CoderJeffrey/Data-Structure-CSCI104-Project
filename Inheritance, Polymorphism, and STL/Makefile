
interpreter: Interpreter.o Statement.h ReturnStatement.o GoSubStatement.o IFStatement.o GotoStatement.o EndStatement.o Arithmetic_Operation.o ProgramState.o LetStatement.o PrintStatement.o 
	g++ -Wall -g $^ -o $@	

Interpreter.o: Interpreter.cpp
	g++ -Wall -g  -c $< -o $@
ReturnStatement.o: ReturnStatement.cpp ReturnStatement.h
	g++ -Wall -g  -c $< -o $@
GoSubStatement.o: GoSubStatement.cpp GoSubStatement.h
	g++ -Wall -g  -c $< -o $@
IFStatement.o: IFStatement.cpp IFStatement.h
	g++ -Wall -g  -c $< -o $@
GotoStatement.o: GotoStatement.cpp GotoStatement.h
	g++ -Wall -g  -c $< -o $@
EndStatement.o: EndStatement.cpp EndStatement.h
	g++ -Wall -g  -c $< -o $@
Arithmetic_Operation.o: Arithmetic_Operation.cpp Arithmetic_Operation.h
	g++ -Wall -g  -c $< -o $@
LetStatement.o: LetStatement.cpp LetStatement.h
	g++ -Wall -g  -c $< -o $@
PrintStatement.o: PrintStatement.cpp PrintStatement.h 
	g++ -Wall -g  -c $< -o $@
ProgramState.o: ProgramState.cpp ProgramState.h 
	g++ -Wall -g  -c $< -o $@

clean:
	rm -rf *.exe *.o