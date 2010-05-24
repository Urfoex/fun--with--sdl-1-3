/* 
 * File:   Fractal.h
 * Author: Manuel Bellersen
 *
 * Created on 16. Mai 2010, 17:40
 */

#ifndef _FRACTAL_H
#define	_FRACTAL_H

#include "Drawable.h"
#include "Triangle.h"
#include "RotTrans.h"
#include <list>

class Fractal : public Drawable {
public:
	Fractal();
	~Fractal();
	void generateFractal( int depth);
	void draw();
	RotTrans rotationTranslation;
private:
	static void drawTriangle( Triangle* t);
	void computeFractal( Triangle* t, int depth );
	double computePerturbation( double length);
	double computeLength( Point* a, Point*b);
	std::list<Triangle*> triangleList;
	std::list<Point*> pointList;
	double highMax;
};

struct tridepth{
	tridepth( Triangle* T, int D){
		triangle = T; depth = D;
	};
	Triangle* triangle;
	int depth;
};


#endif	/* _FRACTAL_H */

