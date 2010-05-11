#include <iostream>
#include "Point.h"

Point::Point( GLdouble X, GLdouble Y, GLdouble Z){
	xyz[0] = X;
	xyz[1] = Y;
	xyz[2] = Z;
};

Point::Point( GLdouble XYZ[3]){
	xyz[0] = XYZ[0];
	xyz[1] = XYZ[1];
	xyz[2] = XYZ[2];
};

Point::~Point(){
	std::cerr << "endPoint\n";
}

void Point::draw(){
	glVertex3dv( xyz);
}
