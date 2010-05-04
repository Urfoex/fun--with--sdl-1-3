/* 
 * File:   main.cpp
 * Author: Manuel Bellersen
 *
 * Created on 1. Mai 2010, 08:24
 */

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <cassert>
#include <string>
#include "OpenGL.h"

using namespace std;

int main( int argc, char** argv ) {

	OpenGL* ogl = OpenGL::getInstance();
    assert( ogl != NULL);

	SDL_WM_SetCaption( "Fraktale Gebirge", NULL);


	    //Move to offset
    glTranslatef( 0, 0, 0 );

    //Start quad
    glBegin( GL_QUADS );

        //Set color to white
        glColor4f( 1.0, 1.0, 1.0, 1.0 );

        //Draw square
	    glVertex3f( 0,            0,             0 );
	    glVertex3f( 40, 0,             0 );
	    glVertex3f( 40, 40, 0 );
	    glVertex3f( 0,            40, 0 );

    //End quad
    glEnd();

    //Reset
    glLoadIdentity();

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(100, 1.00, -1.0);

	glColor4f( 1.0, 0.0, 1.0, 1.0);
	glBegin( GL_POLYGON);
		glVertex3f( 0.0, 0.0, -10);
		glVertex3f( 0.0, 99.0, -10);
		glVertex3f( 0.0, 99.0, 0);
		glVertex3f( 0.0, 99.0, 10);
		glVertex3f( 99.0, 99.0, 10);
		glVertex3f( 99.0, 99.0, 0);
		glVertex3f( 99.0, 0.0 , 0);
		glVertex3f( 99.0, 0.0 , -10);
	glEnd();

	glLoadIdentity();

	do{
		ogl->handleEvents();
		glClearColor( 0, 0, 0, 0);
		glClear( GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapBuffers();
	}while( !ogl->gotQuit());


    OpenGL::Quit();

    return 0;
}

