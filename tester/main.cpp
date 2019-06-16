#include <iostream>
#include "SGE/engine/Engine.hpp"
#include "BoxSpawner.hpp"
#include "Wiggler.hpp"
#include "TestLogic.hpp"
#include <unistd.h>
#include "SFML/Graphics.hpp"
#include "PhysicsBox.hpp"
#include "SGE/utils/Matrix2D.hpp"




int main() {
    /*
    Matrix2D<float> m1(1,3);
    m1[0][0] = 3.0f;
    m1[0][1] = 4.0f;
    m1[0][2] = 2.0f;

    m1.print_matrix("m1");

    Matrix2D<float> m2(3,4);
    m2[0][0] = 13.0f;
    m2[0][1] = 9.0f;
    m2[0][2] = 7.0f;
    m2[0][3] = 15.0f;
    m2[1][0] = 8.0f;
    m2[1][1] = 7.0f;
    m2[1][2] = 4.0f;
    m2[1][3] = 6.0f;
    m2[2][0] = 6.0f;
    m2[2][1] = 4.0f;
    m2[2][2] = 0.0f;
    m2[2][3] = 3.0f;
    m2.print_matrix("m2");

    auto df = (m1 * m2);
    df.print_matrix("Res");
    */

    // TODO make debug_shapes' displaying size indipendent from the view zoom (probably needs some view management implementaition)


    sge::cd::Engine_ConstructionData engine_cd;
    engine_cd.window.vsync_on = true;
    engine_cd.window.view_vertical_size = 30;
    sge::Engine engine (engine_cd);


    sge::cd::SceneConstructionData initial_scene_cd("Wiggle wiggle", new BoxSpawner());
    engine.initialize(initial_scene_cd);

    while (engine.game_loop()) {

    }

    return 0;
}