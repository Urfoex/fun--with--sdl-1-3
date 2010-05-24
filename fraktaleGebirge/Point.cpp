#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include "Point.h"

Point::Point( GLdouble X, GLdouble Y, GLdouble Z):
x(X), y(Y), z(Z){
};

Point::~Point(){
//	std::cerr << "endPoint: " << x << " " <<
//		y << " " << z << "\n";
}

void Point::removePoint(Point* p){
//	std::cerr << "endPoint: " << p->getID() << "/"
//		<< Drawable::getEndID() <<" \n";
	delete p;
}

bool Point::hasEqualPlaceAs(Point* p){
	if( std::abs( std::abs(x) - std::abs( p->x)) < 0.000001
		&& std::abs( std::abs(z) - std::abs( p->z)) < 0.000001){
//		std::cerr << "x: " << x << " px: " << p->x;
//		std::cerr << "z: " << z << " pz: " << p->z << "\n";
		return true;
	}
	return false;
}

void Point::draw(){
	glVertex3d( x, y, z);
}

void Point::printPoints(){
	std::cerr << "x: " << x << "\t"
		<< "y: " << y << "\t"
		<< "z: " << z << "\n";
}

GLdouble Point::getX(){
	return x;
}

GLdouble Point::getY(){
	return y;
}

GLdouble Point::getZ(){
	return z;
}

void Point::alterY(double high){
	y += high;
}
