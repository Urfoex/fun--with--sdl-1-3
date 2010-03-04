#define SDL_NO_COMPAT

#include <iostream>
#include <string>
#include <cstring>
#include <locale>
#include <SDL.h>

#include "main.h"
#include "cEvent.h"
#include "cWindow.h"
#include "cVariable.h"
#include "cDebugConsole.h"

using namespace std;

// part-2
// Mal versuchen den ersten Part ein wenig zu verschönern.
// Zum Beispiel in Klassen packen und mehrere Tasten gleichzeitig drücken
// lassen.

int main( int argc, char** argv){
    if( SDL_Init( SDL_INIT_VIDEO) == -1){
        cerr << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }
    
    string DEBUG = "DEBUG";
    string argString;
    locale loc;
    bool bDebug = false;
    if( argc > 1){
        for( unsigned short int i = 0; i < strlen( argv[1]); ++i)
            argString.push_back( (char)toupper( argv[1][i], loc));
        
        if( !DEBUG.compare( argString)){
            bDebug = true;
        }
    }

    cVariable mainVariable;
    bool RUNNING = true;
    cWindow mainWindow( mainVariable);
    cEvent mainEvent( mainVariable);
    cDebugConsole* mainDebugConsole;
    
    if( bDebug)
        mainDebugConsole = new cDebugConsole( mainVariable);
    
    mainVariable.m_isRunning = &RUNNING;
    mainVariable.m_Main_Event = &mainEvent;
    mainVariable.m_Main_Window = &mainWindow;
    if( bDebug)
        mainVariable.m_Main_Debug_Console = mainDebugConsole;

    mainWindow.createWindow();
    SDL_Thread* mainEventThread = SDL_CreateThread( cEvent::threadedEvents, &mainEvent);
    SDL_Thread* mainDebugConsoleThread = NULL;
    if( bDebug)
        mainDebugConsoleThread = SDL_CreateThread( cDebugConsole::threadedDebugging, mainDebugConsole);

    while( RUNNING){
        while( SDL_PollEvent( &mainEvent.m_Event)){
            SDL_CondSignal( mainEvent.m_Event_Condition);
        }
        mainWindow.renderWindow();
    }
    SDL_WaitThread( mainEventThread, NULL);
    if( bDebug){
        SDL_WaitThread( mainDebugConsoleThread, NULL);
        delete mainDebugConsole;
    }

    return 0;
}


//int main( int argc, char** argv){
//    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
//        cerr << SDL_GetError() << endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    Uint32 mainWindowFlags = SDL_WINDOW_SHOWN;
//    Uint32 mainRenderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTFLIP2;
//
//        globVars::movingPoint.x = 320;
//        globVars::movingPoint.y = 240;
//
//        globVars::movingPointColor.r = 255;
//        globVars::movingPointColor.g = 255;
//        globVars::movingPointColor.b = 255;
//
//    globVars::eventMutex = SDL_CreateMutex();
//    globVars::eventCond = SDL_CreateCond();
//
//    setIsDone( false);
//
//    globVars::mainWindow = SDL_CreateWindow( "Fun with SDL 1.3 - Part 1", 
//                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
//                    640, 480, mainWindowFlags);
//    if( globVars::mainWindow == NULL){
//        cerr << SDL_GetError() << endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    if( SDL_CreateRenderer( globVars::mainWindow, -1, mainRenderFlags)){
//        cerr << SDL_GetError() << endl;
//        SDL_Quit();
//        return -2;
//    }
//
//    SDL_ShowWindow( globVars::mainWindow);
//    SDL_RenderPresent();
//
//    globVars::eventTd = SDL_CreateThread( eventThread, NULL);
//
//    SDL_Event mainEvent;
//    
//    while( !getIsDone()){
//
//        if( SDL_PollEvent( &mainEvent)){
//            globVars::mainEvent = mainEvent;
//            SDL_CondSignal( globVars::eventCond);
//        }
//
//
//        SDL_SelectRenderer( globVars::mainWindow);
//        SDL_SetRenderDrawColor( globVars::movingPointColor.r, globVars::movingPointColor.g, 
//                                globVars::movingPointColor.b, 255);
//        SDL_RenderDrawPoint( globVars::movingPoint.x, globVars::movingPoint.y);
//        SDL_RenderPresent();
//        SDL_Texture
//
//    }
//
//    SDL_WaitThread( globVars::eventTd, NULL);
//
//    SDL_DestroyCond( globVars::eventCond);
//    SDL_DestroyMutex( globVars::eventMutex);
//
//    SDL_DestroyRenderer( globVars::mainWindow);
//    SDL_DestroyWindow( globVars::mainWindow);
//
//    SDL_Quit();
//
//    return 0;
//}
//
//bool getIsDone(){
//    return globVars::isDone;
//}
//
//void setIsDone( bool var){
//        globVars::isDone = var;
//}
//
//int eventThread( void* param){
//    SDL_LockMutex( globVars::eventMutex);
//    while( !getIsDone()){
//        SDL_CondWait( globVars::eventCond, globVars::eventMutex);
//
//        if( globVars::mainEvent.type == SDL_KEYDOWN){
//            switch( globVars::mainEvent.key.keysym.sym){
//            case SDLK_w:
//                globVars::movingPoint.y -= 1;
//                break;
//            case SDLK_a:
//                globVars::movingPoint.x -= 1;
//                break;
//            case SDLK_s:
//                globVars::movingPoint.y += 1;
//                break;
//            case SDLK_d:
//                globVars::movingPoint.x += 1;
//                break;
//            case SDLK_ESCAPE:
//                setIsDone( true);
//                return 0;
//                break;
//            case SDLK_h:
//            case SDLK_j:
//            case SDLK_k:
//            case SDLK_z:
//            case SDLK_u:
//            case SDLK_i:
//
//                if( globVars::movingPointColor.r < 255 && SDLK_z)
//                    globVars::movingPointColor.r += ( globVars::mainEvent.key.keysym.sym == SDLK_h)? 1:0;
//                if( globVars::movingPointColor.g < 255 && SDLK_z)
//                    globVars::movingPointColor.g += ( globVars::mainEvent.key.keysym.sym == SDLK_j)? 1:0;
//                if( globVars::movingPointColor.b < 255 && SDLK_z)
//                    globVars::movingPointColor.b += ( globVars::mainEvent.key.keysym.sym == SDLK_k)? 1:0;
//
//                if( globVars::movingPointColor.r > 0 && SDLK_z)
//                    globVars::movingPointColor.r -= ( globVars::mainEvent.key.keysym.sym == SDLK_z)? 1:0;
//                if( globVars::movingPointColor.g > 0 && SDLK_z)
//                    globVars::movingPointColor.g -= ( globVars::mainEvent.key.keysym.sym == SDLK_u)? 1:0;
//                if( globVars::movingPointColor.b > 0 && SDLK_z)
//                    globVars::movingPointColor.b -= ( globVars::mainEvent.key.keysym.sym == SDLK_i)? 1:0;
//                
//                break;
//            default:
//                break;
//            }
//        }
//        if( globVars::mainEvent.type == SDL_QUIT){
//            setIsDone( true);
//            return 0;
//        }
//
//    }
//    SDL_UnlockMutex( globVars::eventMutex);
//    return 0;
//}
