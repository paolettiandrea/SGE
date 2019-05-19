//
// Created by andrea on 5/1/19.
//

#ifndef FACTORY_EXPERIMENTS_IENVIRONMENT_HPP
#define FACTORY_EXPERIMENTS_IENVIRONMENT_HPP

#include <string>
#include "SGE/Camera.hpp"

namespace sge {
    class Logic;

    namespace debug { class DebugShape; }

    /*!
     * \brief The interface of the Engine to the objects,
     * allowing for query for relevant information about the execution of the game
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
        //virtual double fixed_delta_time() = 0;

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

        virtual void debug_draw(debug::DebugShape* new_debug_shape) = 0;

        virtual Camera* get_camera() = 0;
    };

}




#endif //FACTORY_EXPERIMENTS_IENVIRONMENT_HPP
