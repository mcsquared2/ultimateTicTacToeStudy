#include "debug.h"

void debug(std::string msg) {
    if ( debugOn ) {
        std::cout << msg << std::endl;
    }
}