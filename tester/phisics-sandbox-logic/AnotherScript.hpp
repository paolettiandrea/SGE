//
// Created by andrea on 04/10/19.
//

#ifndef SGE_ANOTHERSCRIPT_HPP
#define SGE_ANOTHERSCRIPT_HPP


#include <SGE/logic/Logic.hpp>

class AnotherScript : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_update() override;
};


#endif //SGE_ANOTHERSCRIPT_HPP
