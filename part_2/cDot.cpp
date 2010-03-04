#ifndef SDL_NO_COMPAT
#define SDL_NO_COMPAT
#endif

#include <SDL.h>
#include "cDot.h"


cDot::cDot(){
    m_Point_Mutex = SDL_CreateMutex();
    m_Color_Mutex = SDL_CreateMutex();
    m_Point_Condition = SDL_CreateCond();
    m_Color_Condition = SDL_CreateCond();
}

cDot::~cDot(){
    SDL_DestroyMutex( m_Point_Mutex);
    SDL_DestroyMutex( m_Color_Mutex);
    SDL_DestroyCond( m_Point_Condition);
    SDL_DestroyCond( m_Color_Condition);
}

void cDot::setPoint( int x, int y){
    SDL_LockMutex( m_Point_Mutex);
    m_Point.x = x;
    m_Point.y = y;
    SDL_UnlockMutex( m_Point_Mutex);
}

void cDot::moveInX( int x){
    SDL_LockMutex( m_Point_Mutex);
    m_Point.x += x;
    SDL_UnlockMutex( m_Point_Mutex);
}

void cDot::moveInY( int y){
    SDL_LockMutex( m_Point_Mutex);
    m_Point.y += y;
    SDL_UnlockMutex( m_Point_Mutex);
}

SDL_Point cDot::getPoint(){
    SDL_LockMutex( m_Point_Mutex);
    SDL_Point tempPoint = m_Point;
    SDL_UnlockMutex( m_Point_Mutex);
    return tempPoint;
}

SDL_Color cDot::getColor(){
    SDL_LockMutex( m_Color_Mutex);
    SDL_Color tempColor = m_Color;
    SDL_UnlockMutex( m_Color_Mutex);
    return tempColor;
}
