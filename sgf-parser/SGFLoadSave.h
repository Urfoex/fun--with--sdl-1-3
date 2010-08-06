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

///***************************************************************************
///***************************************************************************
/// @class SGFLoadSave
/// 
/// Creating, loading and saving SGF trees.
///***************************************************************************
class SGFLoadSave {
public:
    ///***********************************************************************
    /// Constructor.
    ///***********************************************************************
    SGFLoadSave();
    
    ///***********************************************************************
    /// Loading a SGF-tree from a filename.
    /// 
    /// @param filename The name of the file to load.
    /// @return Node of the head of the loaded tree.
    ///***********************************************************************
    SHPNode loadSGF( std::string filename);
    
    ///***********************************************************************
    /// Inserting data from a istream into the current SGF-tree.
    /// 
    /// @param stream The stream where to read from.
    ///***********************************************************************
    void insert( std::istream& stream);
    
    ///***********************************************************************
    /// Inserting data from a string into the current SGF-tree.
    /// 
    /// @param input The character-sequence to insert into the SGF-tree.
    ///***********************************************************************
    void insert( std::string input);
    
    ///***********************************************************************
    /// Changing the current state to the given.
    /// 
    /// @param newState The new state.
    ///***********************************************************************
    void changeState( boost::shared_ptr<STATE::State> newState);
    
    ///***********************************************************************
    /// Returns the SGF-tree.
    /// 
    /// @return The SGF-tree.
    ///***********************************************************************
    SHPNode getSGF();
    
    ///***********************************************************************
    /// Returns the current state.
    /// 
    /// @return The current state.
    ///***********************************************************************
    const STATE::State* const getCurrentState();
    
    ///***********************************************************************
    /// Resets and clears everything.
    ///***********************************************************************
    void reset();
    
    ///***********************************************************************
    /// Saves the SGF-tree into a file.
    /// 
    /// @param filename The filename where to save to.
    ///***********************************************************************
    void save( std::string filename);
    
    ///***********************************************************************
    /// Prints the SGF-tree to the given ostream.
    /// 
    /// @param out The ostream where to print to.
    ///***********************************************************************
    void print( std::ostream& out);
    
    ///***********************************************************************
    /// Returns the SGF-tree as a string.
    /// 
    /// @return The SGF-tree as string.
    ///***********************************************************************
    std::string getTree();

    ///***********************************************************************
    /// Adding a node to the current node.
    ///***********************************************************************
    void addNode ( );
    
    ///***********************************************************************
    /// Shows the error-message.
    /// 
    /// @param error The error-message to show.
    ///***********************************************************************
    void setError ( std::string error );
    
    ///***********************************************************************
    /// Returns the name of the current propertie.
    /// 
    /// @return The current propertie name.
    ///***********************************************************************
    std::string getCurrentPropertieName();
    
    ///***********************************************************************
    /// Returns the name of the current option.
    /// 
    /// @return The current option name.
    ///***********************************************************************
    std::string getCurrentOptionName();
    
    ///***********************************************************************
    /// Sets the current node to the parent node of the current node.
    ///***********************************************************************
    void closeNode ();
    
    ///***********************************************************************
    /// Returns the current character of the insertion.
    /// 
    /// @return The current character of the insertion.
    ///***********************************************************************
    char getCurrentCharacter();
    
    ///***********************************************************************
    /// Adds a propertie to the current node.
    /// 
    /// @param propertie The name of the new propertie.
    ///***********************************************************************
    void addPropertie ( std::string propertie );
    
    ///***********************************************************************
    /// Adds a option to the current propertie.
    /// 
    /// @param option The name of the option.
    ///***********************************************************************
    void addOption ( std::string option );
    
    ///***********************************************************************
    /// Adds a semicolon-information to the current propertie.
    ///***********************************************************************
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
    
    ///***********************************************************************
    /// Closes the current open file.
    ///***********************************************************************
    void closeFile();
    
    ///***********************************************************************
    /// Prints the given node and its subnodes to the given ostream.
    /// 
    /// @param node The node to print.
    /// @param out  The ostream where to print to.
    ///***********************************************************************
    void printNode( SHPNode node, std::ostream& out);
    
    ///***********************************************************************
    /// Prints the tree unter the given node to the given ostream.
    /// 
    /// @param node The node which tree to print.
    /// @param out  The ostream where to print to.
    ///***********************************************************************
    void printTree( SHPNode node, std::ostream& out);
};

#endif
