#include <iostream>
#include "SGE/engine/Engine.hpp"
#include "InitialDummyLogic.hpp"
#include "RecursiveSceneLogic.hpp"
#include <unistd.h>

int main() {
    Engine engine;

    engine.initialize(new RecursiveSceneLogic(0));

    while (engine.game_loop()) {
        sleep(1);
    }


    return 0;
}