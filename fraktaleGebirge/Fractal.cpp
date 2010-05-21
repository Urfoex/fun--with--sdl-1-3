#include "Fractal.h"

#include <iostream>
#include <algorithm>
#include <list>
#include "Point.h"
#include "Triangle.h"

using namespace std;

Fractal::Fractal(){
	triangleList.clear();
    pointList.clear();
}

Fractal::~Fractal(){
    for_each( pointList.begin(), pointList.end(), Point::removePoint);
	for_each( triangleList.begin(), triangleList.end(), Triangle::removeTriangle);
}

void Fractal::generateFractal( int depth){
	Point* a = new Point( 300, 450, 0);
	pointList.push_back(a);
	Point* b = new Point( 0, 150, 0);
	pointList.push_back(b);
	Point* c = new Point( 600, 150, 0);
	pointList.push_back(c);
	Triangle* t = new Triangle( a, b, c);
	computeFractal( t, depth);
	std::cerr << "triangles: " << triangleList.size() << std::endl;
	std::cerr << "points: " << pointList.size() << std::endl;
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
		t->A->printPoints();
		t->B->printPoints();
		t->C->printPoints();
		triangleList.push_back( t);
		return;
	}

	Point* ab = new Point(
		t->A->getX() + (t->B->getX() - t->A->getX())/2.0,
		t->A->getY() + (t->B->getY() - t->A->getY())/2.0,
		t->A->getZ() + (t->B->getZ() - t->A->getZ())/2.0
	);
	pointList.push_back(ab);
	Point* ac = new Point(
		t->A->getX() + (t->C->getX() - t->A->getX())/2.0,
		t->A->getY() + (t->C->getY() - t->A->getY())/2.0,
		t->A->getZ() + (t->C->getZ() - t->A->getZ())/2.0
	);
	pointList.push_back(ac);
	Point* bc = new Point(
		t->B->getX() + (t->C->getX() - t->B->getX())/2.0,
		t->B->getY() + (t->C->getY() - t->B->getY())/2.0,
		t->B->getZ() + (t->C->getZ() - t->B->getZ())/2.0
	);
	pointList.push_back(bc);

	ab->alterZ( depth);
	ac->alterZ( depth);
	bc->alterZ( depth);

	Triangle* a_ab_ac = new Triangle( (t->A), ab, ac);
	Triangle* ab_b_bc = new Triangle( ab, (t->B), bc);
	Triangle* ac_bc_c = new Triangle( ac, bc, (t->C));
	Triangle* ab_bc_ac = new Triangle( ab, bc, ac);

	computeFractal( a_ab_ac, depth - 1);
	computeFractal( ab_b_bc, depth - 1);
	computeFractal( ac_bc_c, depth - 1);
	computeFractal( ab_bc_ac, depth - 1);

	delete t;

}

void Fractal::draw(){
	for_each( triangleList.begin(), triangleList.end(), Fractal::drawTriangle);
}

void Fractal::drawTriangle(Triangle* t){
	t->draw();
}
