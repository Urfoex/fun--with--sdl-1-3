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
	static void removePoint( Point* p);
	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	void alterZ( int high);
	~Point();
	void draw();
	void printPoints();
private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
};

#endif	/* _POINT_H */

