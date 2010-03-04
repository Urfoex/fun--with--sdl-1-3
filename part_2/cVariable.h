#ifndef CVARIABLE_H
#define CVARIABLE_H

class cVariable;

#include "cWindow.h"
#include "cEvent.h"
#include "cDebugConsole.h"

class cVariable{
public:
    cWindow* m_Main_Window;
    cEvent* m_Main_Event;
    cDebugConsole* m_Main_Debug_Console;
    bool* m_isRunning;

    cVariable();
private:

};

#endif
