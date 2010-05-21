#include "Triangle.h"
#include <iostream>

Triangle::Triangle( Point* a, Point* b, Point* c):
A(a), B(b), C(c){
}

Triangle::~Triangle(){
}

void Triangle::removeTriangle(Triangle* t){
	std::cerr << "endTriangle: " << t->getID() << "/"
		<< Drawable::getEndID() <<" \n";
	delete t;
}

void Triangle::draw(){
	glBegin( GL_TRIANGLES);
		A->draw();
		B->draw();
		C->draw();
	glEnd();
}
