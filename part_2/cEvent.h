#ifndef CEVENT_H
#define CEVENT_H

class cEvent;

#include <SDL.h>
#include "cVariable.h"

class cEvent{
public:
    cVariable &m_Main_Variable;
    SDL_Event m_Event;
    SDL_mutex* m_Event_Mutex;
    SDL_cond* m_Event_Condition;

    static int threadedEvents( void* p);
    cEvent( cVariable& Variable);
    ~cEvent();
    void analyseEvent();
private:

};

#endif
