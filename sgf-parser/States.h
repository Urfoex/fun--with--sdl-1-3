#ifndef STATES_H
#define STATES_H

#include <string>

class SGFLoadSave;

namespace STATE {
    
///***************************************************************************
/// @class State
/// 
/// Interface to provide execute-method.
///***************************************************************************
class State {
public:
    ///***********************************************************************
    /// Handles the character corresponding to the current State.
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    virtual void execute( SGFLoadSave* pSGFLoadSave, char input) = 0;
};

///***************************************************************************
/// @class GroupOpen 
/// 
/// For '(' - State.
///***************************************************************************
class GroupOpen : public State {
public:
    ///***********************************************************************
    /// Switching to ';' - State
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    void execute( SGFLoadSave* pSGFLoadSave, char input);
};

///***************************************************************************
/// @class Semicolon
/// 
/// For ';' - State.
///***************************************************************************
class Semicolon : public State {
public:
    ///***********************************************************************
    /// Switching to '(' or befor '[' - State
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    void execute( SGFLoadSave* pSGFLoadSave, char input);
};

///***************************************************************************
/// @class PropertieOpen
/// 
/// For befor '[' - State.
///***************************************************************************
class PropertieOpen : public State {
public:
    ///***********************************************************************
    /// Constructor.
    ///***********************************************************************
    PropertieOpen() : name("") {};
    
    ///***********************************************************************
    /// Switching to '[' - State
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    void execute( SGFLoadSave* pSGFLoadSave, char input);

private:
    std::string name;
};

///***************************************************************************
/// @class Option
/// 
/// For '[' - State.
///***************************************************************************
class Option : public State {
public:
    ///***********************************************************************
    /// Constructor.
    ///***********************************************************************
    Option() : backslash(false), name("") {};
    
    ///***********************************************************************
    /// Switching to ']' - State
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    void execute( SGFLoadSave* pSGFLoadSave, char input);

private:
    bool backslash;
    std::string name;
};

///***************************************************************************
/// @class PropertieClose
/// 
/// For ']' - State.
///***************************************************************************
class PropertieClose : public State {
public:
    ///***********************************************************************
    /// Switching to befor '[' or ';' or ')' - State
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    void execute( SGFLoadSave* pSGFLoadSave, char input);
};

///***************************************************************************
/// @class GroupClose
/// 
/// For ')' - State.
///***************************************************************************
class GroupClose : public State {
public:
    ///***********************************************************************
    /// Constructor.
    ///***********************************************************************
    GroupClose() : wrongInput(false) {};
    
    ///***********************************************************************
    /// Switching to ')' or '(' - State
    /// 
    /// @param pSGFLoadSave The machine to use.
    /// @param input        The next character to handle.
    ///***********************************************************************
    void execute( SGFLoadSave* pSGFLoadSave, char input);
private:
    bool wrongInput;
};

}

#endif
