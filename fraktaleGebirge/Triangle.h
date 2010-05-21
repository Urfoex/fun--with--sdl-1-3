/*
 * File:   Triangle.h
 * Author: Manuel Bellersen
 *
 * Created on 12. Mai 2010, 09:30
 */

#ifndef _TRIANGLE_H
#define	_TRIANGLE_H

#include "Drawable.h"
#include "Point.h"

class Triangle : public Drawable {
public:
	Triangle( Point* a, Point* b, Point* c);
	~Triangle();
	void draw();
	Point *A;
	Point *B;
	Point *C;
private:

};

#endif	/* _TRIANGLE_H */

