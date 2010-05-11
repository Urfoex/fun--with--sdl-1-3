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
#include "Point.h"

using namespace std;

int main( int argc, char** argv ) {

    OpenGL &ogl = OpenGL::getInstance();
    assert( !ogl.gotQuit() );

    SDL_WM_SetCaption( "Fraktale Gebirge", NULL);
	Point a(20,20,0);
	ogl.addDrawable( &a);
	Point b(20,20,0);
	ogl.addDrawable( &b);
	Point c(30,30,0);
	ogl.addDrawable( &c);
	Point d(10,20,0);
	ogl.addDrawable( &d);
	Point e(30,20,0);
	ogl.addDrawable( &e);

	do{
		ogl.handleEvents();
		ogl.drawScreen();
	}while( !ogl.gotQuit());

    OpenGL::Quit();

    return 0;
}

