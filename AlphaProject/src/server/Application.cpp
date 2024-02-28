#include <iostream>

#include "lib/renderer/EntryPoint.h"

int main() {
    std::cout << "Hi from server" << std::endl;
    Renderer::Render();
    return 0;
}