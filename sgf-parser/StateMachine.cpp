#include "StateMachine.h"
#include <string>

StateMachine::StateMachine ( FileReadMachine& fileReadMachine ) :
        _fileReadMachine ( fileReadMachine ) {
}

void StateMachine::start() {
    if ( _fileReadMachine.getNextCharacter() == '(') {
        stateGroup();
    } else {
        _fileReadMachine.showError( static_cast<std::string> ( "start wrong\n" ));
    }
}

void StateMachine::stateGroup ( ) {
    if ( _fileReadMachine.getNextCharacter() == ';' ) {
        _fileReadMachine.addNode ( );
        stateSemicolon();
    } else {
        _fileReadMachine.showError
        ( "stateGroup: \";\" missing\n" );
    }
}

void StateMachine::stateSemicolon ( ) {
    char nextChar;
    do {
        nextChar = _fileReadMachine.getNextCharacter();
    } while ( std::iscntrl(nextChar));
    if ( nextChar == '(' ) {
        stateGroup();
        return;
    }
    if ( nextChar == '[' or ( std::isalpha ( nextChar ) && std::isupper ( nextChar ) ) ) {
        statePropertie();
        return;
    }
    _fileReadMachine.showError
    ( static_cast<std::string> ( "stateSemicolon: \"" ) + nextChar + "\" wrong\n" );
}

void StateMachine::statePropertie ( ) {
    if ( _fileReadMachine.getCurrentCharacter() == '[' ) {
        _fileReadMachine.addPropertie ( "" );
        stateOption();
    } else {
        std::string propName;
        char curChar = _fileReadMachine.getCurrentCharacter();
        do {
            propName.push_back ( curChar );
            curChar = _fileReadMachine.getNextCharacter();
            if ( !( (std::isalpha ( curChar ) && std::isupper ( curChar )) || '[' == curChar )) {
                _fileReadMachine.showError
                ( static_cast<std::string> ( "statePropertie: \"" ) + curChar + "\" wrong\n" );
                return;
            }
        } while ( curChar != '[' );
        _fileReadMachine.addPropertie ( propName );
        stateOption( );
    }
}

void StateMachine::stateOption() {
    std::string optName;
    char curChar = _fileReadMachine.getNextCharacter();
    while ( curChar != ']' ) {
        optName.push_back ( curChar );
        if ( curChar == '\\' ) {
            curChar = _fileReadMachine.getNextCharacter();
            optName.push_back ( curChar );
        }
        curChar = _fileReadMachine.getNextCharacter();
    }
    _fileReadMachine.addOption ( optName, (_fileReadMachine.getNextCharacter() == ';'));
    statePropertieEnd();
}

void StateMachine::statePropertieEnd() {
    char nextChar = _fileReadMachine.getCurrentCharacter();
    while ( std::iscntrl( nextChar)) {
        nextChar = _fileReadMachine.getNextCharacter();
    }
    if ( nextChar == ')' ) {
        stateGroupEnd();
        return;
    }
    if ( nextChar == ';' ) {
        stateSemicolon();
        return;
    }
    if ( nextChar == '(') {
        stateGroup();
        return;
    }
    if ( nextChar == '[' || ( std::isalpha ( nextChar ) && std::isupper ( nextChar ) ) ) {
        statePropertie();
        return;
    }
    _fileReadMachine.showError
    ( static_cast<std::string> ( "statePropertieEnd: \"" ) + nextChar + "\" wrong\n" );
}

void StateMachine::stateGroupEnd() {
    _fileReadMachine.closeNode();
    char nextChar;
    do {
        nextChar = _fileReadMachine.getNextCharacter();
    } while ( std::iscntrl(nextChar));
    if ( nextChar == ')') {
        stateGroupEnd();
        return;
    }
    if ( nextChar == '(') {
        stateGroup();
        return;
    }
    if ( _fileReadMachine.gotEOF()) {
        return;
    }
    _fileReadMachine.showError ( static_cast<std::string> ( "stateGroupEnd: \"" ) + nextChar + "\" wrong\n" );
}
