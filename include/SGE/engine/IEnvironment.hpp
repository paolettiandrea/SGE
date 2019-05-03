//
// Created by andrea on 5/1/19.
//

#ifndef FACTORY_EXPERIMENTS_IENVIRONMENT_HPP
#define FACTORY_EXPERIMENTS_IENVIRONMENT_HPP

#include <string>

namespace sge {
    class Logic;

    /*!
     * \brief The interface of the Engine to the objects,
     * allowing for query for relevant information about the execution of the game
     */
    class IEnvironment {
    public:
        virtual double delta_time() = 0;
        virtual unsigned int frame_count() = 0;
        //virtual double fixed_delta_time() = 0;

        virtual bool book_new_scene_push(const std::string &name, Logic *initial_logic) = 0;
        virtual void doom_top_scene() = 0;

    };
}




#endif //FACTORY_EXPERIMENTS_IENVIRONMENT_HPP
