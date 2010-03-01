#ifndef MAIN_H
#define MAIN_H

bool getIsDone();
void setIsDone( bool var);
int eventThread( void* param);

namespace globVars{

    bool isDone = false;
    SDL_Point movingPoint;
    SDL_Color movingPointColor;
    SDL_Window* mainWindow;
    SDL_Event mainEvent;

    SDL_mutex* eventMutex;
    SDL_cond* eventCond;
    SDL_Thread* eventTd;
}

#endif
