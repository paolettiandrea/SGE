//
// Created by andrea on 6/13/19.
//

#ifndef SGE_BOX_HPP
#define SGE_BOX_HPP

#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/PathRenderer.hpp>

class Box : public  sge::Logic {
public:
    Box(float local_width, float local_height) : m_local_width(local_width), m_local_height(local_height) {}

    std::string get_logic_type_id() override {
        return "Box";
    }

    void on_start() override {
        Logic::on_start();

        sge::Path box_path;
        box_path.append_point(sge::Vec2<float>(m_local_width/2,m_local_height/2));
        box_path.append_point(sge::Vec2<float>(m_local_width/2,-m_local_height/2));
        box_path.append_point(sge::Vec2<float>(-m_local_width/2,-m_local_height/2));
        box_path.append_point(sge::Vec2<float>(-m_local_width/2,m_local_height/2));
        box_path.set_closed(true);

        auto path_renderer = gameobject()->add_component<sge::cmp::PathRenderer>("PathRenderer");
        path_renderer->set_path(box_path);
        path_renderer->set_color_all(sf::Color::White);
    }


    float m_local_width, m_local_height;
};
#endif //SGE_BOX_HPP
