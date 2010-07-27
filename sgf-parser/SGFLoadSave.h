#ifndef SGFLOADSAVE_H
#define SGFLOADSAVE_H

#include "sgf-tree.h"
#include "States.h"
#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <boost/shared_ptr.hpp>

class SGFLoadSave {
public:
    SGFLoadSave();
    SHPNode loadSGF( std::string filename);
    void insert( std::istream& stream);
    void insert( std::string input);
    void changeState( boost::shared_ptr<STATE::State> newState);
    SHPNode getSGF();
    const STATE::State* const getCurrentState();
    void reset();
    void save( std::string filename);
    void print( std::ostream& out);
    std::string getTree();

    void addNode ( );
    void setError ( std::string error );
    std::string getCurrentPropertieName();
    std::string getCurrentOptionName();
    void closeNode ();
    char getCurrentCharacter();
    void addPropertie ( std::string propertie );
    void addOption ( std::string option );
    void addSemicolon();
private:
    boost::shared_ptr<STATE::State> _currentState;
    bool _gotError;
    char _currentChar;
    std::ifstream _file;
    std::string _filename;
    SHPNode _headNode;
    SHPNode _currentNode;
    SHPPropertie _currentPropertie;

    void closeFile();
    void printNode( SHPNode node, std::ostream& out);
    void printTree( SHPNode node, std::ostream& out);
};

#endif
