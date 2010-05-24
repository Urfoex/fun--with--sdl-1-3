#include "Triangle.h"
#include <iostream>
#include <algorithm>

Triangle::Triangle( Point* a, Point* b, Point* c):
A(a), B(b), C(c){
}

Triangle::~Triangle(){
}

void Triangle::removeTriangle(Triangle* t){
//	std::cerr << "endTriangle: " << t->getID() << "/"
//		<< Drawable::getEndID() <<" \n";
	delete t;
}

void Triangle::draw(){
//	glColor3f( 0.6 - (A->getX() + B->getX())/100.,
//		0.6 - (A->getY() + B->getY())/100.,
//		0.6- (A->getZ() + B->getZ())/100.);
	glColor3f( 1. - std::max( std::max( A->getY(), B->getY()), C->getY())/450,
			1. - std::max( std::max( A->getY(), B->getY()), C->getY())/450,
			1. - std::max( std::max( A->getY(), B->getY()), C->getY())/450);

	glBegin( GL_TRIANGLES);
		A->draw();
		B->draw();
		C->draw();
	glEnd();
}
