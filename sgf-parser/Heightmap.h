#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "sgf-tree.h"
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

struct Field {
    signed long int high;
    unsigned char color;
    unsigned short int width;

    Field();
    void print();
};

typedef std::vector< std::vector<Field> > Field2D;

class Heightmap {
public:
    Heightmap();
    void setSGF( SHPNode head);
    void step();
    bool hasNext();
    Field2D getCurrentMap();
    void printMap();
private:
    static const unsigned short int NumberOfFields;
    static const unsigned char BLACK;
    static const unsigned char WHITE;
    Field2D _map;
    SHPNode _head;
    
    void printPos( unsigned short int x, unsigned short int y);

    void adjustHeight();
    void changeHeight( unsigned short int x, unsigned short int y);
    void getCoord( std::string xy, unsigned short int& x, unsigned short int& y);
    void getNext();
    bool checkCurrent();
    void setHandicap();
    void addStone( char color ,std::string pos);
    void addHandicap( char color, std::list<SHPPropertie>::iterator it); 
};

#endif
