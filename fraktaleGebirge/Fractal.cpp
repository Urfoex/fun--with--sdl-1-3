#include "Fractal.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Point.h"
#include "Triangle.h"

using namespace std;

Fractal::Fractal(){
	triangleList.clear();
    pointList.clear();
	srand( time(0));
}

Fractal::~Fractal(){
    for_each( pointList.begin(), pointList.end(), Point::removePoint);
	for_each( triangleList.begin(), triangleList.end(), Triangle::removeTriangle);
}

void Fractal::generateFractal( int depth){
	Point* a = new Point( 300.0, 50.0, 75.0);
	pointList.push_back(a);
	Point* b = new Point( 0.0, 50.0, 0.2);
	pointList.push_back(b);
	Point* c = new Point( 600.0, 50.0, 0.2);
	pointList.push_back(c);
	Triangle* t = new Triangle( a, b, c);

	highMax = depth;

//	computeFractalIterative( t, depth);
	computeFractalRecursive( t, depth);
	triangleList.sort();
	std::cerr << "triangles: " << triangleList.size() << std::endl;
	std::cerr << "points: " << pointList.size() << std::endl;
}

void Fractal::computeFractalIterative(Triangle* t, int depth){
    std::list<tridepth*> l;
    l.clear();
    l.push_back( new tridepth( t, depth));
	tridepth* td;
    while( !l.empty()){
		td = l.front();
		l.pop_front();
		t = td->triangle;
		depth = td->depth;
		delete td;

		if( depth == 0){
//			std::cerr << "Pushing triangle\n";
//			t->A->printPoints();
//			t->B->printPoints();
//			t->C->printPoints();
			triangleList.push_back( t);
			continue;
		}

		--depth;

		Point* ab = new Point(
			t->A->getX() + (t->B->getX() - t->A->getX())/2.0,
			t->A->getY() + (t->B->getY() - t->A->getY())/2.0,
			t->A->getZ() + (t->B->getZ() - t->A->getZ())/2.0
		);
		ab = insertPoint( ab);

		Point* ac = new Point(
			t->A->getX() + (t->C->getX() - t->A->getX())/2.0,
			t->A->getY() + (t->C->getY() - t->A->getY())/2.0,
			t->A->getZ() + (t->C->getZ() - t->A->getZ())/2.0
		);
		ac = insertPoint( ac);

		Point* bc = new Point(
			t->B->getX() + (t->C->getX() - t->B->getX())/2.0,
			t->B->getY() + (t->C->getY() - t->B->getY())/2.0,
			t->B->getZ() + (t->C->getZ() - t->B->getZ())/2.0
		);
		bc = insertPoint(bc);

		ab->alterY( computePerturbation( computeLength( t->A, t->B)));
		ac->alterY( computePerturbation( computeLength( t->A, t->C)));
		bc->alterY( computePerturbation( computeLength( t->B, t->C)));

        Triangle* a_ab_ac = new Triangle( (t->A), ab, ac);
        l.push_back( new tridepth( a_ab_ac, depth));

        Triangle* ab_b_bc = new Triangle( ab, (t->B), bc);
        l.push_back( new tridepth( ab_b_bc, depth));

        Triangle* ac_bc_c = new Triangle( ac, bc, (t->C));
        l.push_back( new tridepth( ac_bc_c, depth));

        Triangle* ab_bc_ac = new Triangle( ab, bc, ac);
        l.push_back( new tridepth( ab_bc_ac, depth));

		delete t;
    }
}

void Fractal::computeFractalRecursive( Triangle* t, int depth ){
	if( depth == 0){
//		std::cerr << "Pushing triangle\n";
//		t->A->printPoints();
//		t->B->printPoints();
//		t->C->printPoints();
		triangleList.push_back( t);
		return;
	}

	Point* ab = new Point(
		t->A->getX() + (t->B->getX() - t->A->getX())/2.0,
		t->A->getY() + (t->B->getY() - t->A->getY())/2.0,
		t->A->getZ() + (t->B->getZ() - t->A->getZ())/2.0
	);
	ab = insertPoint( ab);

	Point* ac = new Point(
		t->A->getX() + (t->C->getX() - t->A->getX())/2.0,
		t->A->getY() + (t->C->getY() - t->A->getY())/2.0,
		t->A->getZ() + (t->C->getZ() - t->A->getZ())/2.0
	);
	ac = insertPoint( ac);

	Point* bc = new Point(
		t->B->getX() + (t->C->getX() - t->B->getX())/2.0,
		t->B->getY() + (t->C->getY() - t->B->getY())/2.0,
		t->B->getZ() + (t->C->getZ() - t->B->getZ())/2.0
	);
	bc = insertPoint(bc);

	ab->alterY( computePerturbation( computeLength( t->A, t->B)));
	ac->alterY( computePerturbation( computeLength( t->A, t->C)));
	bc->alterY( computePerturbation( computeLength( t->B, t->C)));

	Triangle* a_ab_ac = new Triangle( (t->A), ab, ac);
	Triangle* ab_b_bc = new Triangle( ab, (t->B), bc);
	Triangle* ac_bc_c = new Triangle( ac, bc, (t->C));
	Triangle* ab_bc_ac = new Triangle( ab, bc, ac);

	computeFractalRecursive( a_ab_ac, depth - 1);
	computeFractalRecursive( ab_b_bc, depth - 1);
	computeFractalRecursive( ac_bc_c, depth - 1);
	computeFractalRecursive( ab_bc_ac, depth - 1);

	delete t;

}

Point* Fractal::insertPoint(Point* p){
	std::list<Point*>::iterator it = pointList.begin();
	while( it != pointList.end()){
		if( p->hasEqualPlaceAs( *it)){
			delete p;
			return *it;
		}
		++it;
	}

	pointList.push_back(p);
	return p;
}

double Fractal::computeLength(Point* a, Point* b){
	return sqrt(
		pow( a->getX() - b->getX(), 2) +
		pow( a->getY() - b->getY(), 2) +
		pow( a->getZ() - b->getZ(), 2));
}

double Fractal::computePerturbation(double length){
	int vorzeichen = (( rand()%2 < 1)? -1 : 1);
	double fak = (rand() % RAND_MAX);
	fak /= RAND_MAX ;
	double power = pow( length, 1.0-1./highMax);
	double p =  fak * power;
	return 	vorzeichen * p;
		
}

void Fractal::draw(){
	glLoadIdentity();
	rotationTranslation.translate();
	rotationTranslation.rotate();
	for_each( triangleList.begin(), triangleList.end(), Fractal::drawTriangle);
	glLoadIdentity();
}

void Fractal::drawTriangle(Triangle* t){
	t->draw();
}
