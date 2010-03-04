#ifndef CWINDOW_H
#define CWINDOW_H

class cWindow;

#include <SDL.h>
#include "cVariable.h"

class cWindow{
public:
    cVariable &m_Main_Variable;
    SDL_Window* m_Window;
    SDL_Window* m_Debug_Window;
    Uint32 m_Window_Flags;
    Uint32 m_Render_Flags;
    Uint32 m_Debug_Window_Flags;
    Uint32 m_Debug_Render_Flags;
    bool m_show_Debug_Window;

    cWindow( cVariable &Variable);
    ~cWindow();
    SDL_Window* createWindow();
    SDL_Window* showDebugWindow();
    SDL_Window* hideDebugWindow();
    void renderWindow();
private:

};

#endif

