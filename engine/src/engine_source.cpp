#include "engine_header.h"
#include <iostream>

namespace sage {

    void EngineClass::engineFunction() {
        std::cout << "Engine Function Called.\n";

        auto window = gfxCreateWindow(1280, 720);
        auto gfx = gfxCreateContext(window);
    }
}