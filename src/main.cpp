#include "Application.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Application game;
        game.run();
    } catch(std::runtime_error& e) {
        std::cerr 
            << "Main: Error Catched!" << std::endl
            << "Message: " << e.what() << std::endl;

        exit(1);
        
    }
    return 0;
}
