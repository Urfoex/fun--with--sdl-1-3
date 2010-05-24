#include "OpenGL.h"
#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Drawable.h"
#include "Point.h"
#include "Fractal.h"

using namespace std;

OpenGL* OpenGL::instance = NULL;
bool OpenGL::quit = true;
SDL_Event OpenGL::event;
unsigned short int OpenGL::windowX = 0;
unsigned short int OpenGL::windowY = 0;
unsigned short int OpenGL::windowDepth = 0;

OpenGL::OpenGL(){
	mouseActivity = NOTHING;
}

OpenGL::~OpenGL(){
	cerr << "Deleting OpenGL instance\n";
    SDL_Quit();
}

void OpenGL::Abort( AbortType error){
    switch( error){
    case APPNO_ERROR:
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

OpenGL& OpenGL::getInstance(){
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
	return *instance;
}

OpenGL& OpenGL::getInstance( unsigned short int X, unsigned short int Y, unsigned short int Depth){
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
	cerr << "Setting up View ...\n";
	setupView();
	quit = false;
    cerr << "... success.\n";
}

void OpenGL::initSDL(){

	if( SDL_Init( SDL_INIT_VIDEO) == -1){
		OpenGL::Abort( SDL_ERROR);
	}

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

	SDL_Surface* mainSurface = SDL_SetVideoMode( windowX, windowY, windowDepth,
        SDL_OPENGL | SDL_DOUBLEBUF | SDL_GL_DOUBLEBUFFER | SDL_HWACCEL | SDL_HWSURFACE | SDL_HWPALETTE);
	if( mainSurface == NULL){
		OpenGL::Abort( SDL_ERROR);
	}
}

void OpenGL::initGL(){
    glShadeModel( GL_SMOOTH);			// smooth shading on
	glClearColor( 0, 0, 0, 0);			// Hintergrundfarbe: schwarz

    glClearDepth( 1.0);					// depth-Buffer
    glEnable( GL_DEPTH_TEST);			// depth-Test on
    glDepthFunc( GL_LEQUAL);			// Test-Typ
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Auto-Korrektur der Perspektive

	if( glGetError() != GL_NO_ERROR){
        OpenGL::Abort( OPENGL_ERROR);			// bei Fehlern abbrechen
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Bildschirm löschen
}

void OpenGL::setupView(){
	glViewport( 0, 0, windowX, windowY);	// Viewport setzten

	setView();

	if( glGetError() != GL_NO_ERROR){
        OpenGL::Abort( OPENGL_ERROR);			// bei Fehlern abbrechen
    }

}

void OpenGL::handleEvents(){
	while( SDL_PollEvent( &event)){
		switch( event.type){
		case SDL_KEYDOWN:
			eventQKeyDown.push( event.key);
			handleKeyDown();
			break;
		case SDL_KEYUP:
			eventQKeyUp.push( event.key);
			handleKeyUp();
			break;
		case SDL_MOUSEBUTTONDOWN:
			eventQMouseDown.push( event.button);
			handleMouseDown();
			break;
		case SDL_MOUSEBUTTONUP:
			eventQMouseUp.push( event.button);
			handleMouseUp();
			break;
		case SDL_MOUSEMOTION:
			eventQMouseMovement.push( event.motion);
			handleMouseMovement();
			break;
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}
	}
}

void OpenGL::drawScreen(){
	glClearColor( 0, 0, 0, 0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	updateView();

	glColor3f( 1, 1, 1);
	glPointSize( 1);
	for_each( drawableList.begin(), drawableList.end(), Drawable::callDraw);

	glLoadIdentity();

	SDL_GL_SwapBuffers();
}

bool OpenGL::gotQuit(){
	return quit;
}

void OpenGL::addDrawable(Drawable* thing){
	drawableList.push_back( thing);
}

void OpenGL::removeDrawable( Drawable* thing){
	drawableList.remove( thing);
}

void OpenGL::handleMouseMovement(){
	while( !eventQMouseMovement.empty()){
		SDL_MouseMotionEvent mme = eventQMouseMovement.front();
		eventQMouseMovement.pop();
		mouseCoordinates.x += mme.xrel;
		mouseCoordinates.y += mme.yrel;
	}
}

void OpenGL::handleMouseDown(){
	while( !eventQMouseDown.empty()){
		SDL_MouseButtonEvent mbe = eventQMouseDown.front();
		eventQMouseDown.pop();
		switch( mbe.button){
			case 4:
				++windowX;
				++windowY;
				setView();
				break;
			default:
				break;
		}
	}
}

void OpenGL::handleMouseUp(){
	while( !eventQMouseUp.empty()){
		SDL_MouseButtonEvent mbe = eventQMouseUp.front();
		eventQMouseUp.pop();
		switch( mbe.button){
			case 5:
				--windowX;
				--windowY;
				setView();
				break;
			default:
				break;
		}
	}
}

void OpenGL::handleKeyDown(){
	while(!eventQKeyDown.empty()){
		SDL_KeyboardEvent ke = eventQKeyDown.front();
		eventQKeyDown.pop();
		switch( ke.keysym.sym){
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_t:
				setMouseActivity( TRANSLATION);
				break;
			case SDLK_r:
				setMouseActivity( ROTATION);
				break;
			case SDLK_z:
				setMouseActivity( NOTHING);
				break;
			case SDLK_UP:
				zoomFactor += 1;
				break;
			case SDLK_DOWN:
				zoomFactor -= 1;
				break;
			default:
				break;
		}
	}
}

void OpenGL::handleKeyUp(){
	while(!eventQKeyUp.empty()){
		SDL_KeyboardEvent ke = eventQKeyUp.front();
		eventQKeyUp.pop();
		switch( ke.keysym.sym){
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_t:
				break;
			case SDLK_r:
				break;
			case SDLK_z:
				break;
			case SDLK_UP:
				zoomFactor -= 1;
				break;
			case SDLK_DOWN:
				zoomFactor += 1;
				break;
			default:
				break;
		}
	}
}

void OpenGL::setMouseActivity(MouseActivity mouseactivity){
	mouseActivity = mouseactivity;
}

void OpenGL::updateMouse(){
	switch( mouseActivity){
	case NOTHING:
		break;
	case TRANSLATION:
		fractal->rotationTranslation.translate( mouseCoordinates.x, mouseCoordinates.y, 0);
		break;
	case ROTATION:
		fractal->rotationTranslation.rotate( mouseCoordinates.y, 0, 0);
		break;
	default:
		break;
	}
	mouseCoordinates.x = 0;
	mouseCoordinates.y = 0;
}

void OpenGL::updateView(){
	updateMouse();
	zoomView();
}

void OpenGL::zoomView(){
	if( zoomFactor){
		windowX += zoomFactor;
		windowY += zoomFactor;
		setView();
	}
}

void OpenGL::setFractal(Fractal* f){
	fractal = f;
	addDrawable( fractal);
	fractal->rotationTranslation.translate( -300.0, -50.0, 0.0);
	fractal->rotationTranslation.rotate( 0.0, 0.0, 0.0);
}

void OpenGL::setView(){
	glMatrixMode( GL_PROJECTION);		// Projektion setzten
	glLoadIdentity();					// auf Einheitsmatrix zurücksetzten
	glOrtho( -(double)windowX/2.0, (double)windowX/2.0, (double)windowY/2.0, -( double )windowY/2.0, -100.0, 100.0);	// Setzten des Sichtvolumens
	glMatrixMode( GL_MODELVIEW);		// MatrixMode auf ModelView setzten
	glLoadIdentity();					// auf Einheitsmatrix zurücksetzten
}