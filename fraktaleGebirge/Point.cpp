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
	std::cerr << "endPoint: " << xyz[0] << " " <<
		xyz[1] << " " << xyz[2] << "\n";
}

void Point::draw(){
	glVertex3dv( xyz);
}

GLdouble Point::getX(){
	return xyz[0];
}

GLdouble Point::getY(){
	return xyz[1];
}

GLdouble Point::getZ(){
	return xyz[2];
}

void Point::alterZ(int high){
	xyz[2] += 0 +  high;
}
