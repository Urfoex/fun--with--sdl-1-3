#include "Heightmap.h"
#include "SGFLoadSave.h"

#include <string>
#include <iostream>

int main( int argc, char** argv){
    Heightmap h;
    SGFLoadSave sls;
    
    if( argc > 1){
        sls.loadSGF( static_cast<std::string>(argv[1]));
    }else{
        std::cerr << "./hm file.sgf\n";
        return 1;
    }
    h.setSGF( sls.getSGF());
    
    while( h.hasNext()){
        h.printMap();
        h.step();
    }
    return 0;
}