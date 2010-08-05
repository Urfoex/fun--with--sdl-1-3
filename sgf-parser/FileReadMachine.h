#ifndef FILEREADMACHINE_H
#define FILEREADMACHINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include "sgf-tree.h"

///***************************************************************************
///***************************************************************************
/// @class FileReadMachine
///
/// A class to open and read a sgf-file into a tree.
/// 
/// @warning Use SGFLoadSave instead.
/// @see SGFLoadSave
///***************************************************************************
class FileReadMachine {
    public:
        ///*******************************************************************
        /// Constructor.
        ///
        /// @param filename The name of the file to use. 
        ///*******************************************************************
        FileReadMachine( std::string filename);
        
        ///*******************************************************************
        /// Destructor.
        ///*******************************************************************
        ~FileReadMachine(){std::clog << "FRM done\n";};
        
        ///*******************************************************************
        /// Opens the file and starts the StateMachine.
        ///*******************************************************************
        void analyse();
        
        ///*******************************************************************
        /// Gets and returns the next character in the file.
        ///
        /// @return The next character in the file.
        ///*******************************************************************
        char getNextCharacter();
        
        ///*******************************************************************
        /// Returns the current character of the file.
        ///
        /// @return The current character of the file.
        ///*******************************************************************
        char getCurrentCharacter();
        
        ///*******************************************************************
        /// Returns if the file has its eofbit set.
        ///
        /// @return True if eofbit of the file is set.
        ///*******************************************************************
        bool gotEOF();
        
        ///*******************************************************************
        /// Adds a new Node to current Node and sets current Node to this 
        ///  new Node.
        ///*******************************************************************
        void addNode ( );
        
        ///*******************************************************************
        /// Sets current Node to parent Node of current Node.
        ///*******************************************************************
        void closeNode ();
        
        ///*******************************************************************
        /// Adds a new Propertie and sets the current Propertie to this new
        ///  Propertie.
        /// 
        /// @param propertie The name of the new Propertie.
        ///*******************************************************************
        void addPropertie ( std::string propertie );
        
        ///*******************************************************************
        /// Sets the Option and Semicolon-State of the current Propertie.
        /// 
        /// @param option The name of the Option.
        /// @param semicolon Should be set True if the current Propertie
        ///        should end with a semicolon.
        ///*******************************************************************
        void addOption ( std::string option, bool semicolon );
        
        ///*******************************************************************
        /// Shows the given error on std::cerr.
        /// 
        /// @param error The error to show.
        ///*******************************************************************
        void showError ( std::string error );
        
        ///*******************************************************************
        /// Returns the name of the current Propertie.
        /// 
        /// @return The name of the current Propertie.
        ///*******************************************************************
        std::string getCurrentPropertieName();
        
        ///*******************************************************************
        /// Returns the Option of the current Propertie.
        /// 
        /// @return The Option of the current Propertie.
        ///*******************************************************************
        std::string getCurrentOptionName();
        
        ///*******************************************************************
        /// Prints the tree under the given Node.
        /// 
        /// @param node The head Node of the tree to print.
        ///*******************************************************************
        void printTree( SHPNode node);
    private:
        char _currentChar;
        std::ifstream _file;
        std::string _filename;
        SHPNode _headNode;
        SHPNode _currentNode;
        SHPPropertie _currentPropertie;
        
        ///*******************************************************************
        /// Closes the file.
        ///*******************************************************************
        void closeFile();
        
        ///*******************************************************************
        /// Prints the the given node and subnodes.
        /// 
        /// @param node The node to print.
        ///*******************************************************************
        void printNode( SHPNode node);
};

#endif
