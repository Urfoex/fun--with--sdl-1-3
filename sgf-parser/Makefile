all: sgf-parser sgf-ls

sgf-parser: main.o FileReadMachine.o StateMachine.o
	g++ -Wall -o sgf-parser main.o FileReadMachine.o StateMachine.o

main.o: main.cpp


FileReadMachine.o: FileReadMachine.cpp FileReadMachine.h sgf-tree.h


StateMachine.o: StateMachine.cpp StateMachine.h

sgf-ls: main2.o States.o SGFLoadSave.o
	g++ -Wall -o sgf-sl main2.o States.o SGFLoadSave.o

main2.o: main2.cpp

States.o: States.cpp States.h
	g++ -Wall -c States.cpp States.h

SGFLoadSave.o: SGFLoadSave.cpp SGFLoadSave.h
	g++ -Wall -c SGFLoadSave.cpp SGFLoadSave.h	

clean:
	rm -rf *.o sgf-parser sgf-ls