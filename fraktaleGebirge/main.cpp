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
#include "Fractal.h"

using namespace std;

int main( int argc, char** argv ) {

    OpenGL &ogl = OpenGL::getInstance();
    assert( !ogl.gotQuit() );

    SDL_WM_SetCaption( "Fraktale Gebirge", NULL);

	Fractal f;
	f.generateFractal( 07);
	ogl.setFractal( &f);

	do{
		ogl.handleEvents();
		ogl.drawScreen();
	}while( !ogl.gotQuit());

    OpenGL::Quit();

    return 0;
}

