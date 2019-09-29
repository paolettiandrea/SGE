//
// Created by andrea on 5/1/19.
//

#ifndef SGE_IENVIRONMENT_HPP
#define SGE_IENVIRONMENT_HPP

#include <string>
#include <SGE/Path.hpp>
#include <SGE/debug/DebugShape.hpp>
#include "SGE/Camera.hpp"
#include "SGE/Vec2.hpp"

namespace sge {
    class Logic;

    namespace debug { class DebugShape; }

    /*!
     * \brief The interface of the Engine Core exposes to game objects, logic, etc.
     * allowing queries for relevant information about the execution of the game and some Scene stack manipulation
     */
    class IEnvironment {
    public:
        /*!
         * \brief Gets the delta_time, meaning the time (in s) that passed between this frame and the one before
         */
        virtual double delta_time() = 0;
        /*!
         * \brief Gets the frame_count at this moment
         * \return The number of the frame the engine is executing right now.
         */
        virtual unsigned int frame_count() = 0;
        virtual double fixed_delta_time() = 0;

        /*!
         * \brief Books the push of a new Scene on top of the Scene stack. The actual push will happen at the end of this game_loop pass.
         * \param name The name of the Scene that needs to be pushed
         * \param initial_logic The initial Logic to be attached to the initial GameObject of the Scene
         * \return true if the booking was successfull, false if not meaning that some other object have already booked a scene push this frame
         */
        virtual bool book_new_scene_push(const std::string &name, Logic *initial_logic) = 0;
        /*!
         * \brief Dooms the top Scene, flagging it for popping from the Scene stack at the end of this game_loop
         */
        virtual void doom_top_scene() = 0;

        virtual void debug_draw_point(const sge::Vec2<float>& point, float duration=0.f, const std::string& label="", unsigned int digits=1, sf::Color color=SGE_DEFAULT_DEBUG_COLOR) = 0;
        virtual void debug_draw_line(const sge::Vec2<float>& point1, const sge::Vec2<float>& point2, float duration=0.f, const std::string& label="", unsigned int digits=1, sf::Color color=SGE_DEFAULT_DEBUG_COLOR) = 0;
        virtual void debug_draw_path(sge::Path path, float duration=0, const std::string& label="", unsigned int decimals=0, sf::Color color=SGE_DEFAULT_DEBUG_COLOR) = 0;
        virtual void debug_draw_circle(sge::Vec2<float> center_pos, float radius, float duration=0, const std::string& label="", unsigned int decimals=0, sf::Color color=SGE_DEFAULT_DEBUG_COLOR) = 0;
        virtual void debug_draw_direction(sge::Vec2<float> from, sge::Vec2<float> to, float duration=0, sf::Color color=SGE_DEFAULT_DEBUG_COLOR) = 0;
        virtual bool is_shutting_down() = 0;
    };

}




#endif //SGE_IENVIRONMENT_HPP
