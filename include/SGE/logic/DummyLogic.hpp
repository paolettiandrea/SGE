//
// Created by andrea on 4/29/19.
//

#ifndef FACTORY_EXPERIMENTS_DUMMYLOGIC_HPP
#define FACTORY_EXPERIMENTS_DUMMYLOGIC_HPP

#include "Logic.hpp"

class DummyLogic : public  Logic {
public:
    DummyLogic() {}

    void on_start() override;

    void on_destruction() override {
        LOG_DEBUG(3) << "on_destruction";
    }

    std::string get_logic_id() override {
        return "DummyLogic";
    }

};



#endif //FACTORY_EXPERIMENTS_DUMMYLOGIC_HPP
