#ifndef FILEREADMACHINE_H
#define FILEREADMACHINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include "sgf-tree.h"


class FileReadMachine {
    public:
        FileReadMachine( std::string filename);
        ~FileReadMachine(){std::clog << "FRM done\n";};
        void analyse();
        char getNextCharacter();
        char getCurrentCharacter();
        bool gotEOF();
        void addNode ( );
        void closeNode ();
        void addPropertie ( std::string propertie );
        void addOption ( std::string option, bool semicolon );
        void showError ( std::string error );
        std::string getCurrentPropertieName();
        std::string getCurrentOptionName();
        void printTree( SHPNode node);
    private:
        char _currentChar;
        std::ifstream _file;
        std::string _filename;
        SHPNode _headNode;
        SHPNode _currentNode;
        SHPPropertie _currentPropertie;
        
        void closeFile();
        void printNode( SHPNode node);
};

#endif
