#include <iostream>

#include "lib/WhackAMole.h"

int main() {
    WhackAMole whackAMole(10);

    std::cout << "Hello World" << std::endl;

    std::cout << whackAMole.getBoard();

    return 0;
}