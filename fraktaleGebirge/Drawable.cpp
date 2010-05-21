#include "Drawable.h"

unsigned long int Drawable::endID = 0;

Drawable::Drawable(){
	id = ++endID;
};

Drawable::~Drawable(){
	--endID;
};

void Drawable::draw(){
	std::cerr << "virtual\n";
};

bool Drawable::operator==( Drawable const& a){
	return this->id == a.id;
};

void Drawable::callDraw( Drawable* a){
	a->draw();
};