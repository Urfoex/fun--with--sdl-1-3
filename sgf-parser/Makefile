all: sgf-parser

sgf-parser: main.o FileReadMachine.o StateMachine.o
	g++ -Wall -o sgf-parser main.o FileReadMachine.o StateMachine.o

main.o: main.cpp


FileReadMachine.o: FileReadMachine.cpp FileReadMachine.h sgf-tree.h


StateMachine.o: StateMachine.cpp StateMachine.h

