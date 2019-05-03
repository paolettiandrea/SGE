//
// Created by andrea on 5/2/19.
//

#ifndef FACTORY_EXPERIMENTS_RECURSIVESCENELOGIC_HPP
#define FACTORY_EXPERIMENTS_RECURSIVESCENELOGIC_HPP

#include "SGE/logic/Logic.hpp"

class RecursiveSceneLogic : public sge::Logic {
public:
    RecursiveSceneLogic(int _depth) : depth(_depth) {}

    std::string get_logic_type_id() override {
        return "RecursiveSceneLogic";
    }

    void on_start() override {
        LOG_DEBUG(30) << "on_start";
        env()->book_new_scene_push("Recursive scene " + std::to_string(depth+1), new RecursiveSceneLogic(depth+1));
    }

private:
    int depth;
};
#endif //FACTORY_EXPERIMENTS_RECURSIVESCENELOGIC_HPP
