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
	Drawable();
	virtual ~Drawable();
	virtual void draw();
	virtual bool operator==( Drawable const& a);
    static void callDraw( Drawable* a);
private:
	unsigned long int id;
	static unsigned long int endID;

protected:

};

#endif	/* _DRAWABLE_H */

