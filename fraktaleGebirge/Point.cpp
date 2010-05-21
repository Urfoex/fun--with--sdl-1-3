#include <iostream>
#include "Point.h"

Point::Point( GLdouble X, GLdouble Y, GLdouble Z):
x(X), y(Y), z(Z){
};

Point::~Point(){
	std::cerr << "endPoint: " << x << " " <<
		y << " " << z << "\n";
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

void Point::alterZ(int high){
	z += 0 +  high;
}
