#ifndef CDEBUGCONSOLE_H
#define CDEBUGCONSOLE_H

class cDebugConsole;

#include <string>
#include "cVariable.h"

using namespace std;

class cDebugConsole{
public:
    cVariable &m_Main_Variable;
    string m_Input;

    static int threadedDebugging( void* p);
    void doDebugging();
    cDebugConsole( cVariable &Variable);
private:

};

#endif
