#include "States.h"
#include "SGFLoadSave.h"
#include <iostream>

void STATE::GroupOpen::execute( SGFLoadSave* pSGFLoadSave, char input) {
    if ( input == '(') {
        // Holding state
        return;
    }
    if ( input == ';' ) {
        pSGFLoadSave->addNode();
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new STATE::Semicolon()));
    } else {
        pSGFLoadSave->setError( "GroupOpen: \";\" missing\n" );
    }
}

void STATE::Semicolon::execute(SGFLoadSave* pSGFLoadSave, char input) {
    if ( std::iscntrl( input)) {
        // Holding state
        return;
    }
    if ( input == '(' ) {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new GroupOpen()));
        return;
    }
    if ( input == '[' or ( std::isalpha ( input ) && std::isupper ( input ) ) ) {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new PropertieOpen()));
        return;
    }
    if( input == ')'){
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new GroupClose()));
        return;
    }
    pSGFLoadSave->setError
    ( static_cast<std::string> ( "Semicolon: \"" ) + input + "\" wrong\n" );
}

void STATE::PropertieOpen::execute(SGFLoadSave* pSGFLoadSave, char input) {
    if ( pSGFLoadSave->getCurrentCharacter() == '[' ) {
        pSGFLoadSave->addPropertie( name);
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new Option()));
    } else {
        name.push_back( pSGFLoadSave->getCurrentCharacter());
        if ( input == '[') {
            pSGFLoadSave->addPropertie( name);
            pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new Option()));
        } else {
            // Holding state
        }
    }
}

void STATE::Option::execute(SGFLoadSave* pSGFLoadSave, char input) {
    char last = pSGFLoadSave->getCurrentCharacter();
    if( name.empty() && last != '['){
        if ( last == '\\') {
            backslash = true;
        } else {
            backslash = false;
        }
        name.push_back(last);
    }
    if ( input == ']' && !backslash) {
        pSGFLoadSave->addOption( name);
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new PropertieClose()));
    } else {
        if ( input == '\\') {
            backslash = true;
        } else {
            backslash = false;
        }
        name.push_back(input);
        // Holding state
    }
}

void STATE::PropertieClose::execute(SGFLoadSave* pSGFLoadSave, char input) {
    if ( std::iscntrl( input)) {
        // Holding state
        return;
    }
    if ( input == ')' ) {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new GroupClose()));
        return;
    }
    if ( input == ';' ) {
        pSGFLoadSave->addSemicolon();
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new Semicolon()));
        return;
    }
    if ( input == '(') {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new GroupOpen()));
        return;
    }
    if ( input == '[' || ( std::isalpha ( input ) && std::isupper ( input ) ) ) {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new PropertieOpen()));
        return;
    }
    pSGFLoadSave->setError
    ( static_cast<std::string> ( "PropertieClose: \"" ) + input + "\" wrong\n" );
}

void STATE::GroupClose::execute( SGFLoadSave* pSGFLoadSave, char input) {
    if ( wrongInput == false) {
        pSGFLoadSave->closeNode();
    }
    if ( std::iscntrl(input) || std::isspace(input)) {
        // Holding state
        wrongInput = true;
        return;
    }
    if ( input == ')') {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new GroupClose()));
        return;
    }
    if ( input == '(') {
        pSGFLoadSave->changeState( boost::shared_ptr<STATE::State>( new GroupOpen()));
        return;
    }
    if( input == ';'){
        pSGFLoadSave->changeState(boost::shared_ptr<STATE::State>( new Semicolon()));
        return;
    }
    pSGFLoadSave->setError ( static_cast<std::string> ( "GroupClose: \"" ) + input + "\" wrong\n" );
}
