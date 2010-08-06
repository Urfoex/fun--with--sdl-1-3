#ifndef SGF_TREE_H
#define SGF_TREE_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <list>

struct Node;
struct Propertie;

typedef boost::shared_ptr<Node> SHPNode;
typedef boost::shared_ptr<Propertie> SHPPropertie;

///***************************************************************************
/// @struct Propertie
/// 
/// Storing information of the Propertie.
///***************************************************************************
struct Propertie {
    std::string name;
    std::string option;
    bool hasSemicolon;
};

///***************************************************************************
/// @struct Node
/// 
/// Storing Properties and subnodes.
///***************************************************************************
struct Node {
    std::list<SHPNode> nodes;
    std::list<SHPPropertie> properties;
    SHPNode parent;
};

#endif

