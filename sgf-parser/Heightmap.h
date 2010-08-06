#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "sgf-tree.h"
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

///***************************************************************************
///***************************************************************************
/// @struct Field
/// 
/// A class to store information about one field.
///***************************************************************************
struct Field {
    signed long int high;
    unsigned char color;
    unsigned short int width;

    Field();
    void print();
};

typedef std::vector< std::vector<Field> > Field2D;

///***************************************************************************
/// @class Heightmap
/// 
/// Genereting a highmap from a given SGF Node.
///
/// @see Node
///***************************************************************************
class Heightmap {
public:
    ///***********************************************************************
    /// Constructor.
    ///***********************************************************************
    Heightmap();
    
    ///***********************************************************************
    /// Setting the head of the SGF-tree and handicap if found in tree.
    /// 
    /// @param head The head of the SGF-tree.
    ///***********************************************************************
    void setSGF( SHPNode head);
    
    ///***********************************************************************
    /// Doing one step in the tree.
    ///***********************************************************************
    void step();
    
    ///***********************************************************************
    /// Checking if the tree has more to display.
    /// 
    /// @return True if there is more to display in the tree.
    ///***********************************************************************
    bool hasNext();
    
    ///***********************************************************************
    /// Returns the current highmap.
    /// 
    /// @return The current highmap.
    ///***********************************************************************
    Field2D getCurrentMap();
    
    ///***********************************************************************
    /// Prints the current map to std::cout.
    ///***********************************************************************
    void printMap();
private:
    static const unsigned short int NumberOfFields;
    static const unsigned char BLACK;
    static const unsigned char WHITE;
    Field2D _map;
    SHPNode _head;
    
    ///***********************************************************************
    /// Prints the coordinates and values of a given parameter.
    /// 
    /// @param x X-Coordinate
    /// @param y Y-Coordinate
    ///***********************************************************************
    void printPos( unsigned short int x, unsigned short int y);

    ///***********************************************************************
    /// Calls the change-height-method for each field.
    /// 
    /// @see changeHeight
    ///***********************************************************************
    void adjustHeight();
    
    ///***********************************************************************
    /// Changing the height of a given field.
    /// For 'B' +1, 'W' -1, else +0 .
    /// 
    /// @param x X-Coordinate
    /// @param y Y-Coordinate
    ///***********************************************************************
    void changeHeight( unsigned short int x, unsigned short int y);
    
    ///***********************************************************************
    /// Tries to extraced the x and y coordinates of a given string.
    /// 
    /// @param xy String with combind coordinates.
    /// @param x  Returning X-Coordinate extracted from the string.
    /// @param y  Returning Y-Coordinate extracted from the string.
    ///***********************************************************************
    void getCoord( std::string xy, unsigned short int& x, unsigned short int& y);
    
    ///***********************************************************************
    /// Getting the next possible move from the tree.
    ///***********************************************************************
    void getNext();
    
    ///***********************************************************************
    /// Returns if current value from tree is possible move.
    /// 
    /// @return True if value is 'W' or 'B'.
    ///***********************************************************************
    bool checkCurrent();
    
    ///***********************************************************************
    /// Tries to extract a handicap from the tree.
    ///***********************************************************************
    void setHandicap();
    
    ///***********************************************************************
    /// Adds a stone with a given color to a given position.
    /// 
    /// @param color The color of the stone to place.
    /// @param pos   The position where to place the stone.
    ///***********************************************************************
    void addStone( char color ,std::string pos);
    
    ///***********************************************************************
    /// Adds stones from a given color and startiterator to the fields.
    /// 
    /// @param color The color of the handicap-stones.
    /// @param it    The position from where to iterate and get the stones.
    ///***********************************************************************
    void addHandicap( char color, std::list<SHPPropertie>::iterator it); 
};

#endif
