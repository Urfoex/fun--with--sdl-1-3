/* 
 * File:   DataStructures.h
 * Author: Manuel Bellersen
 *
 * Created on 22. Mai 2010, 07:59
 */

#ifndef _DATASTRUCTURES_H
#define	_DATASTRUCTURES_H

#include <SDL_opengl.h>

class RotTrans{
public:
    RotTrans();
    void rotate( GLfloat x, GLfloat y, GLfloat z);
	void translate( GLfloat x, GLfloat y, GLfloat z);
	void rotate();
	void translate();
private:
	GLfloat rotationDegreeX;
	GLfloat rotationDegreeY;
	GLfloat rotationDegreeZ;
	GLshort rotationX;
	GLshort rotationY;
	GLshort rotationZ;
	GLfloat translationX;
	GLfloat translationY;
	GLfloat translationZ;
};

#endif	/* _DATASTRUCTURES_H */

