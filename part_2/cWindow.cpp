#include <iostream>
#include <SDL.h>
#include "cWindow.h"

using namespace std;

cWindow::cWindow( cVariable &Variable): m_Main_Variable( Variable){
    m_Window = NULL;
    m_Debug_Window = NULL;
    m_show_Debug_Window = false;
    m_Window_Flags = SDL_WINDOW_SHOWN;
    m_Render_Flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTFLIP2;
    m_Debug_Window_Flags = SDL_WINDOW_SHOWN;
    m_Debug_Render_Flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTFLIP2;
}

cWindow::~cWindow(){
    if( m_Window){
        SDL_DestroyRenderer( m_Window);
        SDL_DestroyWindow( m_Window);
        m_Window = NULL;
    }
    if( m_Debug_Window){
        SDL_DestroyRenderer( m_Debug_Window);
        SDL_DestroyWindow( m_Debug_Window);
        m_Debug_Window = NULL;
    }
}

SDL_Window* cWindow::createWindow(){
    if( m_Window)
        return m_Window;
    m_Window = SDL_CreateWindow( "Fun with SDL 1.3 - Part 3",
                                 SDL_WINDOWPOS_CENTERED, 
                                 SDL_WINDOWPOS_CENTERED,
                                 640, 480,
                                 m_Window_Flags);
    if( m_Window == NULL){
        cerr << SDL_GetError() << endl;
        return NULL;
    }

    if( SDL_CreateRenderer( m_Window, -1, m_Window_Flags) == -1){
        cerr << SDL_GetError() << endl;
        SDL_DestroyWindow( m_Window);
        return NULL;
    }
    return m_Window;
}

SDL_Window* cWindow::showDebugWindow(){
    if( m_Debug_Window)
        return m_Debug_Window;
    m_Debug_Window = SDL_CreateWindow( "Fun with SDL 1.3 - Part 3",
                                 SDL_WINDOWPOS_CENTERED, 
                                 SDL_WINDOWPOS_CENTERED,
                                 640, 480,
                                 m_Debug_Window_Flags);
    if( m_Debug_Window == NULL){
        cerr << SDL_GetError() << endl;
        return NULL;
    }

    if( SDL_CreateRenderer( m_Debug_Window, -1, m_Debug_Window_Flags) == -1){
        cerr << SDL_GetError() << endl;
        SDL_DestroyWindow( m_Debug_Window);
        return NULL;
    }
    return m_Debug_Window;

}

SDL_Window* cWindow::hideDebugWindow(){
    if( !m_Debug_Window)
        return NULL;
    SDL_HideWindow( m_Debug_Window);
    SDL_DestroyRenderer( m_Debug_Window);
    SDL_DestroyWindow( m_Debug_Window);
    m_Debug_Window = NULL;
    return m_Debug_Window;
}

void cWindow::renderWindow(){
    if( !m_Window){
        cerr << "no window\n";
        return;
    }
    SDL_SelectRenderer( m_Window);
    SDL_RenderPresent();
    if( m_show_Debug_Window){
        SDL_SelectRenderer( m_Debug_Window);
        SDL_RenderPresent();
    }
}

