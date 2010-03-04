#include <iostream>
#include <string>
#include "cDebugConsole.h"

using namespace std;

cDebugConsole::cDebugConsole( cVariable &Variable): m_Main_Variable( Variable){

}


int cDebugConsole::threadedDebugging( void* p){
    cDebugConsole &rDebugConsole = *((cDebugConsole*)p);
    rDebugConsole.doDebugging();
    return 0;
}

void cDebugConsole::doDebugging(){
    cerr << "starting debug: \n";
    while( *m_Main_Variable.m_isRunning){
        getline( cin , m_Input);
        if( cin.fail())
            break;
        cout << m_Input << endl;
        if( !m_Input.compare( "quit")){
            *(m_Main_Variable.m_isRunning) = false;
            SDL_CondSignal( m_Main_Variable.m_Main_Event->m_Event_Condition);
            break;;
        }
    }
    cerr << "ending debug...\n";
}

