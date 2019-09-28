#ifndef SGE_ENGINECORE_HPP
#define SGE_ENGINECORE_HPP

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

#include "ObjectManager.hpp"
#include <chrono>
#include "LogicManager.hpp"
#include "Loggable.hpp"
#include "IEnvironment.hpp"
#include "Engine_ConstructionData.hpp"
#include "WindowManager.hpp"
#include "PhysicsManager.hpp"

namespace sge::core {
    /*!
     * \brief The internal part of the Engine
     */
    class EngineCore : utils::log::Loggable, IEnvironment {
    public:
        /*!
         * \brief Constructs the core
         * \param data The user defined data necessay in order to construct this object
         */
        explicit EngineCore(cd::Engine_ConstructionData& data)
                : Loggable("ENGINE CORE")
                , object_manager((IEnvironment*)this)
                , window_manager (data.window)
                , physics_manager(data.physics){  }


    public:

        virtual ~EngineCore();

        /*!
         * \brief The actual method containing the game loop
         * \return true if the core is still running, false otherwise
         */
        bool game_loop();

        /*!
         * \brief The initialization method of the core
         * \param initial_scene_cd The construction data for the initial Scene the core needs to be initialized with
         */
        void initialize(cd::SceneConstructionData& initial_scene_cd);

        //region IEnvironment declarations

        double delta_time() override;

        void visual_debug_pass();

    private:
        double fixed_delta_time() override;

        unsigned int frame_count() override;

        bool book_new_scene_push(const std::string &name, Logic *initial_logic) override;

        void doom_top_scene() override;

        Camera *get_camera() override;

        bool is_shutting_down() override;

        bool m_shutting_down_flag = false;
        //endregion


    private:
        ObjectManager object_manager;
        LogicManager logic_manager;
        WindowManager window_manager;
        PhysicsManager physics_manager;

        unsigned int m_frame_counter = 0;

        double m_delta_time = 0;
        double m_physics_time_accumulator = 0;
        std::chrono::time_point<std::chrono::steady_clock> last_toop_start_time;

        void debug_draw_point(const sge::Vec2<float>& point, float duration, const std::string& label, unsigned int digits, sf::Color color) override;
        void debug_draw_line(const sge::Vec2<float>& point1, const sge::Vec2<float>& point2, float duration, const std::string& label, unsigned int digits, sf::Color color) override;
        void debug_draw_path(sge::Path path, float duration, const std::string& label, unsigned int decimals, sf::Color color) override;
        void debug_draw_circle(sge::Vec2<float> center_pos, float radius, float duration, const std::string& label, unsigned int decimals, sf::Color color) override;

        void debug_draw_direction(sge::Vec2<float> from, sge::Vec2<float> to, float duration, sf::Color color) override;
    };


}





#endif //SGE_ENGINECORE_HPP





/*!
\file
\brief Header file.
*/