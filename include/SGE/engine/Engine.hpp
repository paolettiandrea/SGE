#ifndef SGE_ENGINE_HPP
#define SGE_ENGINE_HPP

#include "SGE/utils/log/Loggable.hpp"
#include "SGE/engine/IEnvironment.hpp"
#include "SGE/engine/construction_data/Engine_ConstructionData.hpp"

namespace sge {
    namespace core {
        class EngineCore;
    }
    class Logic;

    /*!
 * \brief The engine object (entry side)
 */
    class Engine : public utils::log::Loggable {
    public:
        /*!
         * \brief Constructs the engine, which will be ready for initialization after this.
         * \param data The object holding all the user defined data necessary for the construction
         */
        Engine(cd::Engine_ConstructionData& data);
        virtual ~Engine();
        /*!
         * \brief Executes one pass of the game loop
         * \return true if the Engine is still running, false otherwise
         */
        bool game_loop();
        /*!
         * \brief Gets a pointer to the environment
         * \return A pointer to IEnvironment
         */
        IEnvironment* env();

        /*!
         * \brief Initializes the engine, getting it ready for game_loop execution
         * \param initial_scene_cd The construction data for the initial Scene the Engine will be initialized with.
         */
        void initialize(cd::SceneConstructionData& initial_scene_cd);

    private:
        core::EngineCore* core;
    };
}







#endif //SGE_ENGINE_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/