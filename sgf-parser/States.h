#ifndef STATES_H
#define STATES_H

#include <string>

class SGFLoadSave;

namespace STATE {
class State {
public:
    virtual void execute( SGFLoadSave* pSGFLoadSave, char input) = 0;
};

class GroupOpen : public State {
public:
    void execute( SGFLoadSave* pSGFLoadSave, char input);
};

class Semicolon : public State {
public:
    void execute( SGFLoadSave* pSGFLoadSave, char input);
};

class PropertieOpen : public State {
public:
    PropertieOpen() : name("") {};
    void execute( SGFLoadSave* pSGFLoadSave, char input);

private:
    std::string name;
};

class Option : public State {
public:
    Option() : backslash(false), name("") {};
    void execute( SGFLoadSave* pSGFLoadSave, char input);

private:
    bool backslash;
    std::string name;
};

class PropertieClose : public State {
public:
    void execute( SGFLoadSave* pSGFLoadSave, char input);
};

class GroupClose : public State {
public:
    GroupClose() : wrongInput(false) {};
    void execute( SGFLoadSave* pSGFLoadSave, char input);
private:
    bool wrongInput;
};

}

#endif
