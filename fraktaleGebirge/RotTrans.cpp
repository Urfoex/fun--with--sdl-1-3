#include "RotTrans.h"

RotTrans::RotTrans(){
	rotationDegreeX = 0.0;
	rotationDegreeY = 0.0;
	rotationDegreeZ = 0.0;
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;
	translationX = 0.0;
	translationY = 0.0;
	translationZ = 0.0;
}

void RotTrans::rotate( GLfloat x, GLfloat y, GLfloat z){
	rotationDegreeX += x;
	rotationDegreeY += y;
	rotationDegreeZ += z;

	if( rotationDegreeX || x){
		rotationX = 1;
	}
	if( rotationDegreeY || y){
		rotationY = 1;
	}
}

void RotTrans::translate(GLfloat x, GLfloat y, GLfloat z){
	translationX += x;
	translationY += y;
	translationZ += z;
}

void RotTrans::rotate(){
	glRotatef( rotationDegreeX, rotationX, 0, 0);
	rotationX = 0;
}

void RotTrans::translate(){
	glTranslatef( translationX, translationY, translationZ);
}