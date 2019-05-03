//
// Created by andrea on 5/3/19.
//

#ifndef FACTORY_EXPERIMENTS_ENGINECORE_CONSTRUCTIONDATA_HPP
#define FACTORY_EXPERIMENTS_ENGINECORE_CONSTRUCTIONDATA_HPP

#include "WindowManager_ConstructionData.hpp"
#include "SGE/SceneConstructionData.hpp"


namespace sge {
    class Logic;

    namespace cd {
        struct EngineCore_ConstructionData {
            EngineCore_ConstructionData()
                 {};

            WindowManager_ConstructionData window;
        };
    }

}

#endif //FACTORY_EXPERIMENTS_ENGINECORE_CONSTRUCTIONDATA_HPP
