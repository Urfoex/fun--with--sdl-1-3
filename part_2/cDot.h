#ifndef CDOT_H
#define CDOT_H

#ifndef SDL_NO_COMPAT
#define SDL_NO_COMPAT
#endif

#include <SDL.h>

class cDot{
public:
    SDL_Point getPoint();
    void setPoint( int x, int y);
    void moveInX( int x);
    void moveInY( int y);
    SDL_Color getColor();
    void setColor( Uint8 r, Uint8 g, Uint8 b);
private:
    SDL_Point m_Point;
    SDL_Color m_Color;
    SDL_mutex* m_Point_Mutex;
    SDL_mutex* m_Color_Mutex;
    SDL_cond* m_Point_Condition;
    SDL_cond* m_Color_Condition;
} 

#endif
