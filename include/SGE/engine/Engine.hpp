#ifndef FACTORY_EXPERIMENTS_ENGINE_HPP
#define FACTORY_EXPERIMENTS_ENGINE_HPP

#include "SGE/utils/log/Loggable.hpp"
#include "SGE/engine/IEnvironment.hpp"
#include "SGE/engine/construction_data/EngineCore_ConstructionData.hpp"

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
        Engine(cd::EngineCore_ConstructionData& data);
        virtual ~Engine();

        bool game_loop();
        /*!
         * \brief Gets a pointer to the environment
         * \return A pointer to IEnvironment
         */
        IEnvironment* env();


        void initialize(cd::SceneConstructionData& initial_scene_cd);

    private:
        core::EngineCore* core;
    };
}







#endif //FACTORY_EXPERIMENTS_ENGINE_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/