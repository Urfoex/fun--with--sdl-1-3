#include <iostream>
#include "cEvent.h"

using namespace std;


int cEvent::threadedEvents( void* p){
    cEvent &rEvent = *((cEvent*)p);
    rEvent.analyseEvent();
    return 0;
}

cEvent::cEvent( cVariable& Variable): m_Main_Variable( Variable){
    m_Event_Mutex = SDL_CreateMutex();
    m_Event_Condition = SDL_CreateCond();
}

cEvent::~cEvent(){
    SDL_DestroyMutex( m_Event_Mutex);
    SDL_DestroyCond( m_Event_Condition);
}

void cEvent::analyseEvent(){
    SDL_LockMutex( m_Event_Mutex);
    while( *(m_Main_Variable.m_isRunning) == true){
        SDL_CondWait( m_Event_Condition, m_Event_Mutex);
        switch( m_Event.type){
        case SDL_KEYDOWN:
            switch( m_Event.key.keysym.sym){
            case SDLK_ESCAPE:
                *(m_Main_Variable.m_isRunning) = false;
                break;
            default:
                cerr << SDL_GetKeyName( m_Event.key.keysym.sym) << endl;
                break;
            }
            break;
        }                               
    }
    SDL_UnlockMutex( m_Event_Mutex);
}

