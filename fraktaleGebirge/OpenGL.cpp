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
	rotationDegree = 0;
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;
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
	quit = false;
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
			handleKeyDown();
			break;
		case SDL_MOUSEBUTTONDOWN:
			eventQMouseDown.push( event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			eventQMouseUp.push( event.button);
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
	glClear( GL_COLOR_BUFFER_BIT);

	glTranslatef( 0, 0, 0);
	glRotatef( rotationDegree, rotationX, rotationY, rotationZ);
	glColor3f( 1, 1, 1);
	glPointSize( 1);
	for_each( drawableList.begin(), drawableList.end(), Drawable::callDraw);



//	    //Move to offset
//    glTranslatef( 0, 0, 0 );
//
//    //Start quad
//    glBegin( GL_QUADS );
//
//        //Set color to white
//        glColor4f( 1.0, 1.0, 1.0, 1.0 );
//
//        //Draw square
//	    glVertex3f( 0,            0,             0 );
//	    glVertex3f( 40, 0,             0 );
//	    glVertex3f( 40, 40, 0 );
//	    glVertex3f( 0,            40, 0 );
//
//    //End quad
//    glEnd();
//
//    //Reset
//    glLoadIdentity();
//
//	glMatrixMode( GL_MODELVIEW);
//	glLoadIdentity();
//
//	glTranslatef(100, 1.00, -1.0);
//
//	glColor4f( 1.0, 0.0, 1.0, 1.0);
//	glBegin( GL_POLYGON);
//		glVertex3f( 0.0, 0.0, -10);
//		glVertex3f( 0.0, 99.0, -10);
//		glVertex3f( 0.0, 99.0, 0);
//		glVertex3f( 0.0, 99.0, 10);
//		glVertex3f( 99.0, 99.0, 10);
//		glVertex3f( 99.0, 99.0, 0);
//		glVertex3f( 99.0, 0.0 , 0);
//		glVertex3f( 99.0, 0.0 , -10);
//	glEnd();

	glLoadIdentity();


	SDL_GL_SwapBuffers();
}

void OpenGL::rotateView(GLfloat d, GLfloat x, GLfloat y, GLfloat z){
	rotationDegree = d;
	rotationX = x;
	rotationY = y;
	rotationZ = z;
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
//	while( !eventQMouseMovement.empty()){
//		SDL_MouseMotionEvent mme = eventQMouseMovement.front();
//		eventQMouseMovement.pop();
//		rotateView( mme.x/100, 1.0, 0.0, 0);
//		rotateView( mme.y/100, 0.0, 1.0, 0);
//	}
}

void OpenGL::handleKeyDown(){
	while(!eventQKeyDown.empty()){
		SDL_KeyboardEvent ke = eventQKeyDown.front();
		eventQKeyDown.pop();
		switch( ke.keysym.sym){
			case SDLK_ESCAPE:
				quit = true;
				break;
			default:
				break;
		}
	}
}