//
// Created by andrea on 5/3/19.
//

#ifndef SGE_ENGINE_CONSTRUCTIONDATA_HPP
#define SGE_ENGINE_CONSTRUCTIONDATA_HPP

#include "WindowManager_ConstructionData.hpp"
#include "SGE/Scene_ConstructionData.hpp"
#include "SGE/engine/construction_data/PhysicsManager_ConstructionData.hpp"


namespace sge {
    class Logic;

    namespace cd {
        /*!
         * \brief Contains all the user dependent inormation  necessary to construct (but not initialize!) the engine
         */
        struct Engine_ConstructionData {

            /*!
             * \brief The construction data related to the window and the video output of the engine
             */
            WindowManager_ConstructionData window;
            PhysicsManager_ConstructionData physics;
        };
    }

}

#endif //SGE_ENGINE_CONSTRUCTIONDATA_HPP
