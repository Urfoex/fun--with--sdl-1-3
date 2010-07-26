#include <iostream>
#include <fstream>
#include <string>
#include "SGFLoadSave.h"

int main( int argc, char** argv) {
    if ( argc < 2) {
        std::cerr << "Bitte sgf-Datei angeben.\n";
        std::cerr << "Benutzung: sgf-parser datei.sgf\n";
        return 0;
    }
    
    SGFLoadSave sls;
    sls.loadSGF(static_cast<std::string>(argv[1]));
    
    std::clog << "analyse done\n";
    
    return 0;
}
