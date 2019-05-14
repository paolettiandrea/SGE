#include <iostream>
#include "SGE/engine/Engine.hpp"
#include "WigglerSpawner.hpp"
#include "Wiggler.hpp"
#include "HierarchyTestLogic.hpp"
#include <unistd.h>
#include "SFML/Graphics.hpp"


int main() {

    // TODO make debug_shapes' displaying size indipendent from the view zoom (probably needs some view management implementaition)


    sge::cd::Engine_ConstructionData engine_cd;
    engine_cd.window.vsync_on = false;
    engine_cd.window.view_vertical_size = 1000;
    sge::Engine engine (engine_cd);

    sge::cd::SceneConstructionData initial_scene_cd("Wiggle wiggle", new WigglerSpawner(6000));
    engine.initialize(initial_scene_cd);

    while (engine.game_loop()) {

    }

    return 0;
}