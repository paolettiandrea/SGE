#ifndef SGE_ENGINECORE_HPP
#define SGE_ENGINECORE_HPP

#include "ObjectManager.hpp"
#include <chrono>
#include <subsystems/input-manager/InputManager.hpp>
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
    class EngineCore : public utils::log::Loggable, public IEnvironment {
    public:
        /*!
         * \brief Constructs the core
         * \param data The user defined data necessay in order to construct this object
         */
        explicit EngineCore(cd::Engine_ConstructionData& data)
                : Loggable("ENGINE CORE")
                , object_manager((IEnvironment*)this)
                , window_manager (data.window)
                , physics_manager(data.physics)
                , input_manager(){
        }


    public:

        virtual ~EngineCore();

        /*!
         * \brief The actual method containing the game loop
         * \return true if the core is still running, false otherwise
         */
        virtual bool game_loop();

        /*!
         * \brief The initialization method of the core
         * \param initial_scene_cd The construction data for the initial Scene the core needs to be initialized with
         */
        void initialize(cd::Scene_ConstructionData& initial_scene_cd);

        //region IEnvironment declarations

        double delta_time() override;

        void visual_debug_pass();

    protected:
        double fixed_delta_time() override;

        unsigned int frame_count() override;

        bool book_new_scene_push(const std::string &name, Logic *initial_logic) override;

        void doom_top_scene() override;

        bool is_shutting_down() override;

        bool m_shutting_down_flag = false;

    public:
        sf::Vector2u get_window_size() override;

        void doom_scenes(unsigned int number) override;

        int get_scene_number() override;

        void quit() override;


    protected:
        //endregion

        virtual void update_accumulator();
        virtual void physics_routine();
        virtual void render_routine();

        ObjectManager object_manager;
        LogicManager logic_manager;
        WindowManager window_manager;
        PhysicsManager physics_manager;
        InputManager input_manager;

        unsigned int m_frame_counter = 0;

        double m_delta_time = 0;
        double m_physics_time_accumulator = 0;
        std::chrono::time_point<std::chrono::steady_clock> last_loop_start_time;

        void debug_draw_point(const sge::Vec2<float>& point, float duration, const std::string& label, unsigned int digits, sf::Color color) override;
        void debug_draw_line(const sge::Vec2<float>& point1, const sge::Vec2<float>& point2, float duration, const std::string& label, unsigned int digits, sf::Color color) override;
        void debug_draw_path(sge::Path path, float duration, const std::string& label, unsigned int decimals, sf::Color color) override;
        void debug_draw_circle(sge::Vec2<float> center_pos, float radius, float duration, const std::string& label, unsigned int decimals, sf::Color color) override;

        void debug_draw_direction(sge::Vec2<float> from, sge::Vec2<float> to, float duration, sf::Color color) override;

        bool is_mouse_down(sf::Mouse::Button button) override;

        bool is_mouse_released(sf::Mouse::Button button) override;

        bool is_mouse_pressed(sf::Mouse::Button button) override;

        bool is_key_down(sf::Keyboard::Key key) override;

        bool is_key_pressed(sf::Keyboard::Key key) override;

        bool is_key_released(sf::Keyboard::Key key) override;

    public:
        int get_collision_layer_index_from_id(const std::string &id) override;

        bool is_top_scene_doomed() override;

    protected:


        void handle_events();

        void memory_buffer_pass();
    };


}





#endif //SGE_ENGINECORE_HPP





/*!
\file
\brief Header file.
*/