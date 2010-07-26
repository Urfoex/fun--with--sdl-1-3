#ifndef SGFLOADSAVE_H
#define SGFLOADSAVE_H

#include "sgf-tree.h"
#include "States.h"
#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>

class SGFLoadSave {
public:
    SGFLoadSave();
    boost::shared_ptr<Node> loadSGF( std::string filename);
    void changeState( boost::shared_ptr<STATE::State> newState);
    boost::shared_ptr<Node> getSGF();
    const STATE::State* const getCurrentState();

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
    void printNode( SHPNode node);
    void printTree( SHPNode node);
};

#endif
