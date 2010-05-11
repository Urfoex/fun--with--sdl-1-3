/* 
 * File:   Drawable.h
 * Author: Manuel Bellersen
 *
 * Created on 5. Mai 2010, 10:22
 */

#ifndef _DRAWABLE_H
#define	_DRAWABLE_H

#include <iostream>


class Drawable{
public:
	Drawable(){ id = ++endID;};
	virtual ~Drawable(){ --endID;};
	virtual void draw(){ std::cerr << "virtual\n";};
	bool operator==( Drawable const& a){ return this->id == a.id;};
    static void callDraw( Drawable* a){ a->draw();};
private:
	unsigned long int id;
	static unsigned long int endID;

protected:

};

#endif	/* _DRAWABLE_H */

