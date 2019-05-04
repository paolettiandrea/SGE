//
// Created by andrea on 5/3/19.
//

#ifndef FACTORY_EXPERIMENTS_ENGINE_CONSTRUCTIONDATA_HPP
#define FACTORY_EXPERIMENTS_ENGINE_CONSTRUCTIONDATA_HPP

#include "WindowManager_ConstructionData.hpp"
#include "SGE/SceneConstructionData.hpp"


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
        };
    }

}

#endif //FACTORY_EXPERIMENTS_ENGINE_CONSTRUCTIONDATA_HPP
