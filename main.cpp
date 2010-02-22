#include <iostream>
#include <SDL.h>

using namespace std;

// part-1
// Hier beginnen meine ersten SDL 1.3 Gehversuche.
// Es werden Fenster erstellt, initialisiert und darauf rum gezeichnet.

int main( int argc, char** argv){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
        cerr << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window *mainWindow = NULL;
    Uint32 mainWindowFlags = SDL_WINDOW_SHOWN;
    Uint32 mainRenderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTFLIP2;

    SDL_Event mainEvent;
    bool isDone = false;

    SDL_Point movingPoint;
    SDL_Color movingPointColor;
    movingPoint.x = 320;
    movingPoint.y = 240;
    movingPointColor.r = 255;
    movingPointColor.g = 255;
    movingPointColor.b = 255;

    mainWindow = SDL_CreateWindow( "Fun with SDL 1.3 - Part 1", 
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                    640, 480, mainWindowFlags);
    if( mainWindow == NULL){
        cerr << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    SDL_CreateRenderer( mainWindow, -1, mainRenderFlags);

    SDL_ShowWindow( mainWindow);
    SDL_RenderPresent();

    while( !isDone){
        if( SDL_PollEvent( &mainEvent)){
            if( mainEvent.type == SDL_KEYDOWN){
                switch( mainEvent.key.keysym.sym){
                case SDLK_w:
                    --movingPoint.y;
                    break;
                case SDLK_a:
                    --movingPoint.x;
                    break;
                case SDLK_s:
                    ++movingPoint.y;
                    break;
                case SDLK_d:
                    ++movingPoint.x;
                    break;
                case SDLK_ESCAPE:
                    isDone = true;
                    break;
                case SDLK_h:
                    (movingPointColor.r == 255)? movingPointColor.r : ++movingPointColor.r;
                    break;
                case SDLK_j:
                    (movingPointColor.g == 255)? movingPointColor.g : ++movingPointColor.g;
                    break;
                case SDLK_k:
                    (movingPointColor.b == 255)? movingPointColor.b : ++movingPointColor.b;
                    break;
                case SDLK_z:
                    (movingPointColor.r == 0)? movingPointColor.r : --movingPointColor.r;
                    break;
                case SDLK_u:
                    (movingPointColor.g == 0)? movingPointColor.g : --movingPointColor.g;
                    break;
                case SDLK_i:
                    (movingPointColor.b == 0)? movingPointColor.b : --movingPointColor.b;
                    break;
                default:
                    break;
                }
            }
            if( mainEvent.type == SDL_QUIT){
                isDone = true;
            }
        }
        SDL_SetRenderDrawColor( movingPointColor.r, movingPointColor.g, movingPointColor.b, 255);
        SDL_RenderDrawPoint( movingPoint.x, movingPoint.y);
        SDL_RenderPresent();
    }

    SDL_DestroyRenderer( mainWindow);
    SDL_DestroyWindow( mainWindow);

    SDL_Quit();

    return 0;
}
