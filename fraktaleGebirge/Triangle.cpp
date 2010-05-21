#include "Triangle.h"
#include <iostream>

Triangle::Triangle( Point* a, Point* b, Point* c):
A(a), B(b), C(c){
}

Triangle::~Triangle(){
	if( A != NULL){
		delete A;
		A = NULL;
	}
	if( B != NULL){
		delete B;
		B = NULL;
	}
	if( C != NULL){
		delete C;
		C = NULL;
	}
}

void Triangle::draw(){
	glBegin( GL_TRIANGLES);
		A->draw();
		B->draw();
		C->draw();
	glEnd();
}
