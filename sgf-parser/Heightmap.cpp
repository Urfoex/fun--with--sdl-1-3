#include "Heightmap.h"
#include <iostream>
#include <iomanip>

const unsigned short int Heightmap::NumberOfFields = 19;
const unsigned char Heightmap::BLACK = 'B';
const unsigned char Heightmap::WHITE = 'W';

Heightmap::Heightmap() {
    _map.resize(NumberOfFields);
    for ( short int i = 0; i < NumberOfFields; ++i) {
        _map.at(i).resize(NumberOfFields);
    }

    _ended = false;
}

void Heightmap::setSGF(SHPNode head) {
    _head = head;
}

void Heightmap::getNext() {
    while ( checkNext() == false) {
        if ( _head->properties.size() == 0) {
            if ( _head->nodes.size() > 0) {
                _head = _head->nodes.back();
            } else {
                return;
            }
        } else {
            _head->properties.pop_front();
        }
    } 
}

bool Heightmap::checkNext() {
    if ( _head->properties.size() > 0) {
        std::string color = _head->properties.front()->name;
        if ( (color == "B" || color == "W")) {
            return true;
        }
    }
    return false;
}

bool Heightmap::hasNext() {
    return !(_head->nodes.empty() && _head->properties.empty());
}

void Heightmap::step() {
    getNext();
    if ( hasNext()) {
        unsigned short int x,y;
        std::string color = _head->properties.front()->name;
        std::string xy;

        xy = _head->properties.front()->option;
        getCoord( xy, x, y);
        _map.at(x).at(y).color = color.at(0);
        adjustHeight();
    }
    if( _head->properties.size() > 0)
        _head->properties.pop_front();
}

void Heightmap::getCoord(std::string xy, short unsigned int& x, short unsigned int& y) {
    unsigned short int a = 97;
    std::cerr << xy.at(0) << " --- " << xy.at(1) << std::endl;
    x = xy.at(1) - a;
    y = xy.at(0) - a;
}

void Heightmap::printPos( short unsigned int x, short unsigned int y) {
    std::clog << "X: " << x << " Y: " << y << std::endl;
    _map.at(x).at(y).print();
}

void Heightmap::adjustHeight() {
    for ( unsigned short int x = 0; x < _map.size(); ++x) {
        for ( unsigned short int y = 0; y < _map.at(x).size(); ++y) {
            changeHeight( x, y);
        }
    }
}

void Heightmap::changeHeight(short unsigned int x, short unsigned int y) {
    signed short int add = 0;
    switch ( _map.at(x).at(y).color) {
    case BLACK:
        add = 1;
        break;
    case WHITE:
        add = -1;
        break;
    default:
        break;
    }
    _map.at(x).at(y).high += add;
}

void Heightmap::printMap() {
    for ( unsigned short int x = 0; x < _map.size(); ++x) {
        for ( unsigned short int y = 0; y < _map.at(x).size(); ++y) {

            std::cout << std::setw(6) << std::setfill(' ')<<  _map.at(x).at(y).high;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Field::Field() {
    high = 0;
    color = '\0';
    width = 0;
}

void Field::print() {
    std::clog << "high: " << high << " color: " << color << " width: " << width << std::endl;
}
