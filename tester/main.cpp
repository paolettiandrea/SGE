#include <iostream>
#include "SGE/engine/Engine.hpp"
#include "InitialDummyLogic.hpp"
#include "RecursiveSceneLogic.hpp"
#include <unistd.h>
#include "SFML/Graphics.hpp"


int main() {
    sge::Engine engine;

    engine.initialize(new RecursiveSceneLogic(0));

    while (engine.game_loop() && engine.env()->frame_count()<4) {
        sleep(1);
    }

    return 0;
}