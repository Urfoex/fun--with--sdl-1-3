#include "Fractal.h"

#include <iostream>
#include <algorithm>
#include <list>
#include "Point.h"
#include "Triangle.h"

using namespace std;

Fractal::Fractal(){
	triangleList.clear();
}

Fractal::~Fractal(){
	for_each( triangleList.begin(), triangleList.end(), Fractal::removeTriangle);

}

void Fractal::removeTriangle(Triangle* t){
	std::cerr << "endTriangle: \n";
	delete t;
}

void Fractal::generateFractal( int depth){
	Point a( 100, 0, 0);
	Point b( 0, 100, 0);
	Point c( 200, 100, 0);
	Triangle* t = new Triangle( a, b, c);
	computeFractal( t, depth);

}

/*
 * Fraktal:
 * 	Dreieck mit drei Punkten
 * 	4 kleinere innere Dreiecke an gleiche Fkt. übergeben
 * 	Übergabe der noch zu tätigenden Iterationen
 * 	wenn It.Ende -> Punkte verbinden
 *
 *
 */
void Fractal::computeFractal( Triangle* t, int depth ){
	if( depth == 0){
		std::cerr << "Pushing triangle\n";
		t->A.printPoints();
		t->B.printPoints();
		t->C.printPoints();
		triangleList.push_back( t);
		return;
	}

	Point ab(
		t->A.getX() + (t->B.getX() - t->A.getX())/2.0,
		t->A.getY() + (t->B.getY() - t->A.getY())/2.0,
		t->A.getZ() + (t->B.getZ() - t->A.getZ())/2.0
	);
	Point ac(
		t->A.getX() + (t->C.getX() - t->A.getX())/2.0,
		t->A.getY() + (t->C.getY() - t->A.getY())/2.0,
		t->A.getZ() + (t->C.getZ() - t->A.getZ())/2.0
	);
	Point bc(
		t->B.getX() + (t->C.getX() - t->B.getX())/2.0,
		t->B.getY() + (t->C.getY() - t->B.getY())/2.0,
		t->B.getZ() + (t->C.getZ() - t->B.getZ())/2.0
	);

	ab.alterZ( depth);
	ac.alterZ( depth);
	bc.alterZ( depth);

	Triangle* a_ab_ac = new Triangle( (t->A), ab, ac);
	Triangle* ab_b_bc = new Triangle( ab, (t->B), bc);
	Triangle* ac_bc_c = new Triangle( ac, bc, (t->C));
	Triangle* ab_bc_ac = new Triangle( ab, bc, ac);

	computeFractal( a_ab_ac, depth - 1);
	computeFractal( ab_b_bc, depth - 1);
	computeFractal( ac_bc_c, depth - 1);
	computeFractal( ab_bc_ac, depth - 1);

}

void Fractal::draw(){
	for_each( triangleList.begin(), triangleList.end(), Fractal::drawTriangle);
}

void Fractal::drawTriangle(Triangle* t){
	t->draw();
}
