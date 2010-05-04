#include "OpenGL.h"
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
using namespace std;

OpenGL* OpenGL::instance = NULL;
bool OpenGL::quit = false;
SDL_Event OpenGL::event;
unsigned short int OpenGL::windowX = 0;
unsigned short int OpenGL::windowY = 0;
unsigned short int OpenGL::windowDepth = 0;

OpenGL::OpenGL(){
}

OpenGL::~OpenGL(){
	cerr << "Deleting OpenGL instance\n";
    SDL_Quit();
}

void OpenGL::Abort( AbortType error){
    switch( error){
    case NO_ERROR:
        cerr << "Error unknown.\n";
        break;
	case APP_REINITIALIZING:
		cerr << "Reinitializing.\n";
		break;
    case SDL_ERROR:
        cerr << SDL_GetError() << endl;
        break;
    case OPENGL_ERROR:
        cerr << getGLError( glGetError()) << endl;
        break;
    };
    OpenGL::Quit();
}

void OpenGL::Quit(){
    if( instance != NULL){
        delete instance;
        instance = NULL;
    }
}

string OpenGL::getGLError(GLenum error){
    switch( error){
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_TABLE_TOO_LARGE:
        return "GL_OUT_OF_MEMORY";
    }
    return "UNDEFINED_ERROR";
}

OpenGL* OpenGL::getInstance(){
	if( instance == NULL){
		cerr << "Creating OpenGL instance\n";
		if( windowX == 0 || windowY == 0 || windowDepth == 0){
			cerr << "Setting default window x = 640, y = 480, depth = 32.\n";
			windowX = 640;
			windowY = 480;
			windowDepth = 32;
		}else{
			cerr << "Setting x = " << windowX << ", y = " << windowY << ", depth = " << windowDepth << ".\n";
		}
		instance = new OpenGL();
        instance->init();
	}
	return instance;
}

OpenGL* OpenGL::getInstance( unsigned short int X, unsigned short int Y, unsigned short int Depth){
	windowX = X;
	windowY = Y;
	windowDepth = Depth;
	if( instance != NULL){
		Abort( APP_REINITIALIZING);
	}
	return getInstance();
}

void OpenGL::init(){
    cerr << "Initializing SDL ...\n";
	initSDL();
    cerr << "Initializing OpenGL ...\n";
	initGL();
    cerr << "... success.\n";
}

void OpenGL::initSDL(){
	if( SDL_Init( SDL_INIT_VIDEO) == -1){
		OpenGL::Abort( SDL_ERROR);
	}

	SDL_Surface* mainSurface = SDL_SetVideoMode( windowX, windowY, windowDepth, SDL_OPENGL | SDL_DOUBLEBUF);
	if( mainSurface == NULL){
		OpenGL::Abort( SDL_ERROR);
	}
}

void OpenGL::initGL(){
	glClearColor( 0, 0, 0, 0);			// Hintergrundfarbe: schwarz
	glMatrixMode( GL_PROJECTION);		// Projektion setzten
	glOrtho( 0, windowX, windowY, 0, -1, 1);	// Setzten des Sichtvolumens

	glMatrixMode( GL_MODELVIEW);		// MatrixMode auf ModelView setzten
	glLoadIdentity();					// auf Einheitsmatrix zurücksetzten

	if( glGetError() != GL_NO_ERROR){
        OpenGL::Abort( OPENGL_ERROR);			// bei Fehlern abbrechen
    }
	glViewport( 0, 0, windowX, windowY);
    glClear( GL_COLOR_BUFFER_BIT);		// Bildschirm löschen
}

void OpenGL::handleEvents(){
	while( SDL_PollEvent( &event)){
		switch( event.type){
		case SDL_KEYDOWN:
			eventQKeyDown.push( event.key);
			break;
		case SDL_KEYUP:
			eventQKeyUp.push( event.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			eventQMouseDown.push( event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			eventQMouseUp.push( event.button);
			break;
		case SDL_MOUSEMOTION:
			eventQMouseMovement.push( event.motion);
			break;
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}
	}
}

bool OpenGL::gotQuit(){
	return quit;
}
