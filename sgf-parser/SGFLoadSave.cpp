#include "SGFLoadSave.h"
#include <iostream>
#include <sstream>

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


SGFLoadSave::SGFLoadSave( ) {
    reset();
}

void SGFLoadSave::printTree( SHPNode node, std::ostream& out) {
    for ( std::list<SHPNode>::iterator itN = node->nodes.begin(); itN != node->nodes.end(); ++itN) {
        printNode( *itN, out);
    }
}

void SGFLoadSave::printNode(SHPNode node, std::ostream& out) {
    out << "(;";
    for ( std::list<SHPPropertie>::iterator itP = node->properties.begin(); itP != node->properties.end(); ++itP) {
        out << itP->get()->name << "[" << itP->get()->option << "]" << ((itP->get()->hasSemicolon)?";":"");
    }
    out << std::endl;
    for ( std::list<SHPNode>::iterator itN = node->nodes.begin(); itN != node->nodes.end(); ++itN) {
        printNode( *itN, out);
    }
    out << ")" << std::endl;
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

SHPNode SGFLoadSave::loadSGF(std::string filename) {
    reset();
    _filename = filename;
    _file.open( _filename.c_str(), std::ifstream::in);
    if ( _file.is_open()) {
        std::clog << "start done\n";
        _currentState = boost::shared_ptr<STATE::GroupOpen>(new STATE::GroupOpen());

        _currentChar = '\0';
        insert( _file);

        closeFile();
//         printTree( _headNode);
    }
    return _headNode;
}

void SGFLoadSave::insert( std::istream& stream) {
    char in;
    while ( stream.good()) {
        in = stream.get();
        if ( stream.good()) {
            _currentState->execute( this, in);
            if ( _gotError == true) {
                std::cerr << "aborting ...\n";
                reset();
                break;
            }
            _currentChar = in;
        }
    }
}

void SGFLoadSave::insert(std::string input) {
    std::stringstream tmp(input, std::stringstream::in | std::stringstream::out);
    insert( tmp);
}

void SGFLoadSave::changeState(boost::shared_ptr< STATE::State > newState) {
    _currentState = newState;
}

SHPNode SGFLoadSave::getSGF() {
    return _headNode;
}

void SGFLoadSave::reset() {
    _currentChar = '\0';
    _currentPropertie = SHPPropertie();
    _headNode = SHPNode(new Node());
    _currentNode = _headNode;
    _currentState = boost::shared_ptr<STATE::GroupOpen>(new STATE::GroupOpen());
    if ( _file.is_open()) {
        _file.close();
    }
    _filename = "";
    _gotError = false;
}

void SGFLoadSave::print( std::ostream& out) {
    printTree( _headNode, out);
    out.flush();
}

std::string SGFLoadSave::getTree() {
    std::stringstream sstream;
    print( sstream);
    return sstream.str();
}

void SGFLoadSave::save(std::string filename) {
    std::ofstream file;
    file.open( filename.c_str(), std::ofstream::out);
    if ( file.is_open() && file.good()) {
        print( file);
    }
    file.close();
}
