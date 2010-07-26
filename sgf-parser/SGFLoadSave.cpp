#include "SGFLoadSave.h"
#include <iostream>

void SGFLoadSave::addNode ( ) {
    SHPNode newNode( new Node());
    newNode->parent = _currentNode;
    _currentNode->nodes.push_back(SHPNode( newNode));
    _currentNode = newNode;
}

void SGFLoadSave::setError ( std::string error ) {
    closeFile();
    _gotError = true;
    std::cerr << error << std::endl;
    std::cerr << getCurrentPropertieName() << " : " << getCurrentOptionName() << std::endl;
}

void SGFLoadSave::closeFile() {
    if ( _file.is_open())
        _file.close();
}

const STATE::State* const SGFLoadSave::getCurrentState() {
    return _currentState.get();
}


SGFLoadSave::SGFLoadSave( ) : _filename( "") , _headNode( SHPNode(new Node())) {
    _currentNode = _headNode;
}

void SGFLoadSave::printTree( SHPNode node) {
    for ( std::list<SHPNode>::iterator itN = node->nodes.begin(); itN != node->nodes.end(); ++itN) {
        printNode( *itN);
    }
}

void SGFLoadSave::printNode(SHPNode node) {
    std::cout << "(;";
    for ( std::list<SHPPropertie>::iterator itP = node->properties.begin(); itP != node->properties.end(); ++itP) {
        std::cout << itP->get()->name << "[" << itP->get()->option << "]" << ((itP->get()->hasSemicolon)?";":"");
    }
    std::cout << std::endl;
    for ( std::list<SHPNode>::iterator itN = node->nodes.begin(); itN != node->nodes.end(); ++itN) {
        printNode( *itN);
    }
    std::cout << ")" << std::endl;
}

void SGFLoadSave::addOption ( std::string option ) {
    _currentPropertie->option = option;
}

void SGFLoadSave::addSemicolon() {
    _currentPropertie->hasSemicolon = true;
}

void SGFLoadSave::addPropertie ( std::string propertie ) {
    _currentPropertie.reset(new Propertie());
    _currentPropertie->name = propertie;
    _currentPropertie->hasSemicolon = false;
    _currentNode->properties.push_back( _currentPropertie);
}

void SGFLoadSave::closeNode() {
    _currentNode = _currentNode->parent;
}

char SGFLoadSave::getCurrentCharacter() {
    return _currentChar;
}

std::string SGFLoadSave::getCurrentPropertieName() {
    return _currentPropertie->name;
}

std::string SGFLoadSave::getCurrentOptionName() {
    return _currentPropertie->option;
}

boost::shared_ptr< Node > SGFLoadSave::loadSGF(std::string filename) {
    _filename = filename;
    _file.open( _filename.c_str(), std::ifstream::in);
    if ( _file.is_open()) {
        std::clog << "start done\n";
        _currentState = boost::shared_ptr<STATE::GroupOpen>(new STATE::GroupOpen());
        char in;
        _currentChar = '\0';
        while ( _file.good()) {
            in = _file.get();
            if ( _file.good()) {
                _currentState->execute( this, in);
                _currentChar = in;
            }
        }

        closeFile();
        printTree( _headNode);
    }
    return _headNode;
}

void SGFLoadSave::changeState(boost::shared_ptr< STATE::State > newState) {
    _currentState = newState;
}

boost::shared_ptr< Node > SGFLoadSave::getSGF() {
    return _headNode;
}