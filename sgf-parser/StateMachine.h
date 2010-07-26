#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <boost/scoped_ptr.hpp>
#include <iostream>
#include "FileReadMachine.h"

class StateMachine {
    public:
        StateMachine ( FileReadMachine& fileReadMachine );
        ~StateMachine() { std::clog << "SM done\n";};
        
        void start();
        
    private:
        FileReadMachine& _fileReadMachine;
        
        void stateGroup ( );
        void stateSemicolon ( );
        void statePropertie ( );
        void stateOption ( );
        void statePropertieEnd ( );
        void stateGroupEnd ( );
};

#endif
