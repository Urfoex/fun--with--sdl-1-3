#include "FileReadMachine.h"
#include "StateMachine.h"
#include <iostream>
#include <list>


FileReadMachine::FileReadMachine(std::string filename) :
        _filename( filename) , _headNode( SHPNode(new Node())) {
    _currentNode = _headNode;
}

void FileReadMachine::analyse() {
    _file.open( _filename.c_str(), std::ifstream::in);
    if ( _file.is_open()) {
        StateMachine sm( *this );
        sm.start();
        std::clog << "start done\n";
        closeFile();
        printTree( _headNode);
    }
}

void FileReadMachine::printTree( SHPNode node){
    for( std::list<SHPNode>::iterator itN = node->nodes.begin(); itN != node->nodes.end(); ++itN){
        printNode( *itN);        
    }
}

void FileReadMachine::printNode(SHPNode node){
    std::cout << "(;";
    for( std::list<SHPPropertie>::iterator itP = node->properties.begin(); itP != node->properties.end(); ++itP){
        std::cout << itP->get()->name << "[" << itP->get()->option << "]" << ((itP->get()->hasSemicolon)?";":"");
    }
    for( std::list<SHPNode>::iterator itN = node->nodes.begin(); itN != node->nodes.end(); ++itN){
        printNode( *itN);        
    }
    std::cout << ")" << std::endl;
}

void FileReadMachine::addNode ( ) {
    SHPNode newNode( new Node());
    newNode->parent = _currentNode;
    _currentNode->nodes.push_back(SHPNode( newNode));
    _currentNode = newNode;
}

bool FileReadMachine::gotEOF() {
    return _file.eof();
}

void FileReadMachine::addOption ( std::string option, bool semicolon ) {
    _currentPropertie->option = option;
    _currentPropertie->hasSemicolon = semicolon;
}

void FileReadMachine::addPropertie ( std::string propertie ) {
    _currentPropertie.reset(new Propertie());
    _currentPropertie->name = propertie;
    _currentNode->properties.push_back( _currentPropertie);
}

void FileReadMachine::closeNode() {
    _currentNode = _currentNode->parent;
}

char FileReadMachine::getCurrentCharacter() {
    return _currentChar;
}

char FileReadMachine::getNextCharacter() {
    _currentChar = static_cast<char>(_file.get());
    return _currentChar;
}

void FileReadMachine::showError ( std::string error ) {
    closeFile();
    std::cerr << error << std::endl;
    std::cerr << getCurrentPropertieName() << " : " << getCurrentOptionName() << std::endl;
}

void FileReadMachine::closeFile() {
    if ( _file.is_open())
        _file.close();
}

std::string FileReadMachine::getCurrentPropertieName() {
    return _currentPropertie->name;
}

std::string FileReadMachine::getCurrentOptionName() {
    return _currentPropertie->option;
}


