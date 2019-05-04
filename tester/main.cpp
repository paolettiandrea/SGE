#include <iostream>
#include "SGE/engine/Engine.hpp"
#include "InitialDummyLogic.hpp"
#include "RecursiveSceneLogic.hpp"
#include <unistd.h>
#include "SFML/Graphics.hpp"


int main() {


    sge::cd::Engine_ConstructionData engine_cd;
    sge::Engine engine (engine_cd);

    sge::cd::SceneConstructionData initial_scene_cd("Initial recursive scene", new RecursiveSceneLogic(0));
    engine.initialize(initial_scene_cd);

    while (engine.game_loop()) {

    }

    return 0;
}