#ifndef NON_GRAVITAR_ENGINECOREDEBUG_HPP
#define NON_GRAVITAR_ENGINECOREDEBUG_HPP

#include "EngineCore.hpp"
#include <Profiler.hpp>
#include <debug/fps-counter/FpsCounter.hpp>
#include "HierarchyPanel.hpp"



#define SGE_DEBUG_MAIN_KEY1 sf::Keyboard::LControl
#define SGE_DEBUG_MAIN_KEY2 sf::Keyboard::RControl

namespace sge {
    namespace  core {
        class EngineCoreDebug : public EngineCore {
        public:
            explicit EngineCoreDebug(cd::Engine_ConstructionData &data);

        protected:
            void render_routine() override;

            void physics_routine() override;

        private:
            debug::HierarchyPanel hierarchy_panel;
            debug::Profiler profiler;
            debug::FpsCounter fps_counter;


            void handle_debug_input();

            bool hierarchy_active = false;
            bool profiler_active = false;
            bool axis_active = false;


            void draw_axis();

        public:
            bool game_loop() override;
        };
    }
}



#endif //NON_GRAVITAR_ENGINECOREDEBUG_HPP
