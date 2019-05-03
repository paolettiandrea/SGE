#ifndef FACTORY_EXPERIMENTS_WINDOWMANAGER_CONSTRUCTIONDATA_HPP
#define FACTORY_EXPERIMENTS_WINDOWMANAGER_CONSTRUCTIONDATA_HPP

#include <string>
namespace sge::cd {
    struct WindowManager_ConstructionData {
        std::string window_title = "My window";
        unsigned int window_width = 880;
        unsigned int window_height = 495;
        int window_pos_x = 10;
        int window_pos_y = 10;

    };
}


#endif //FACTORY_EXPERIMENTS_WINDOWMANAGER_CONSTRUCTIONDATA_HPP
