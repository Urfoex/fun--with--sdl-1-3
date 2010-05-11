/* 
 * File:   Point.h
 * Author: Manuel Bellersen
 *
 * Created on 5. Mai 2010, 10:28
 */

#ifndef _POINT_H
#define	_POINT_H

#include "Drawable.h"
#include "OpenGL.h"

class Point : public Drawable{
public:
	Point( GLdouble X, GLdouble Y, GLdouble Z);
	Point( GLdouble XYZ[3]);
	~Point();
	void draw();
private:
	GLdouble xyz[3];
};

#endif	/* _POINT_H */

