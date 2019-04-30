#include <iostream>
#include "SGE/Engine.hpp"
#include "InitialDummyLogic.hpp"
#include <unistd.h>

int main() {
    Engine engine;

    Logic* dummy_logic = new InitialDummyLogic();
    engine.initialize(dummy_logic);

    while (engine.game_loop()) {
        sleep(1);
    }


    return 0;
}