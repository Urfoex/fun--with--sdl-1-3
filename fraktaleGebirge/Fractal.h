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
#include <list>

class Fractal : public Drawable {
public:
	Fractal();
	~Fractal();
	void generateFractal( int depth);
	void draw();

private:
	static void drawTriangle( Triangle* t);
	static void removeTriangle( Triangle* t);
	void computeFractal( Triangle* t, int depth );
	std::list<Triangle*> triangleList;
};


#endif	/* _FRACTAL_H */

