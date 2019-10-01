//
// Created by andrea on 01/10/19.
//

#ifndef SGE_STATICPOLYGON_HPP
#define SGE_STATICPOLYGON_HPP


#include <SGE/logic/Logic.hpp>

class StaticPolygon : public sge::Logic {
public:
    explicit StaticPolygon(const sge::Path& path) {
        this->path = path;
    }
    std::string get_logic_type_id() override;

    void on_start() override;

private:
    sge::Path path;
};


#endif //SGE_STATICPOLYGON_HPP
