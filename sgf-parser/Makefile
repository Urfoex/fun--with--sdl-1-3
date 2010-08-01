CPP = g++
CPPFLAGS = -g -Wall -std=c++0x

all: sgf-parser sgf-ls

sgf-parser: main.o FileReadMachine.o StateMachine.o
	g++ -Wall -o sgf-parser main.o FileReadMachine.o StateMachine.o

main.o: main.cpp

FileReadMachine.o: FileReadMachine.cpp FileReadMachine.h sgf-tree.h

StateMachine.o: StateMachine.h StateMachine.cpp

sgf-ls: main2.o States.o SGFLoadSave.o
	g++ -Wall -o sgf-ls main2.o States.o SGFLoadSave.o

main2.o: main2.cpp

States.o: States.h States.cpp

SGFLoadSave.o: SGFLoadSave.h SGFLoadSave.cpp

hm: main3.o Heightmap.o SGFLoadSave.o States.o
	g++ -o hm -Wall main3.o  Heightmap.o SGFLoadSave.o States.o

main3.o: main3.cpp

Heightmap.o: Heightmap.cpp Heightmap.h

clean:
	rm -rf *.o *.gch sgf-parser sgf-ls