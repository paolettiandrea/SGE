#ifndef NON_GRAVITAR_ENGINECOREDEBUG_HPP
#define NON_GRAVITAR_ENGINECOREDEBUG_HPP

#include <debug/profiler/Profiler.hpp>
#include "EngineCore.hpp"
#include "HierarchyPanel.hpp"

#define SGE_DEBUG_FONT "braciola-bold"

#define SGE_DEBUG_COLLIDER_COLOR sf::Color::Green
#define SGE_DEBUG_TRANSFORM_COLOR sf::Color::Red
#define SGE_DEBUG_UI_COLOR sf::Color::Purple


#define SGE_DEBUG_MAIN_KEY1 sf::Keyboard::LControl
#define SGE_DEBUG_MAIN_KEY2 sf::Keyboard::RControl

namespace sge {
    namespace  core {
        class EngineCoreDebug : public EngineCore {
        public:
            explicit EngineCoreDebug(cd::Engine_ConstructionData &data);

        protected:
            void render_routine() override;

        private:
            debug::HierarchyPanel hierarchy_panel;
            //Profiler profiler;
        public:

        private:

            void handle_debug_input();

        public:
            bool game_loop() override;
        };
    }
}



#endif //NON_GRAVITAR_ENGINECOREDEBUG_HPP
