#include <iostream>
#include "SGE/engine/Engine.hpp"
#include "InitialDummyLogic.hpp"
#include <unistd.h>

int main() {
    Engine engine;

    engine.initialize(new InitialDummyLogic());

    while (engine.game_loop()) {
        sleep(1);
    }


    return 0;
}