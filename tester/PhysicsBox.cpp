//
// Created by andrea on 4/30/19.
//

#include "PhysicsBox.hpp"
#include <cmath>

#include "SGE/components/physics/Rigidbody.hpp"
#include "SGE/components/physics/BoxCollider.hpp"
#include "SGE/components/graphics/PathRenderer.hpp"

std::string PhysicsBox::get_logic_type_id() {
    return "PhysicsBox";
}

void PhysicsBox::on_start() {
    LOG(10) << "on_start";

    auto rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    if (m_dynamic)
        rigidbody->set_body_type(b2BodyType::b2_dynamicBody);
    else
        rigidbody->set_body_type((b2BodyType::b2_staticBody));

    auto box_collider = gameobject()->add_component<sge::cmp::BoxCollider>("BoxCollider");
    box_collider->set_height(m_height);
    box_collider->set_width(m_width);
    box_collider->set_restitution(0.9);

    sge::Path contour_path;
    contour_path.append_point(sge::Vec2<float>(m_width/2,m_height/2));
    contour_path.append_point(sge::Vec2<float>(-m_width/2,m_height/2));
    contour_path.append_point(sge::Vec2<float>(-m_width/2,-m_height/2));
    contour_path.append_point(sge::Vec2<float>(m_width/2,-m_height/2));

    auto path_renderer = gameobject()->add_component<sge::cmp::PathRenderer>("PathRenderer");
    path_renderer->set_path(contour_path);
    path_renderer->set_thickness(0.1);
    path_renderer->set_closed(true);
    path_renderer->set_color_all(sf::Color::Blue);

    //env()->doom_top_scene();
}

void PhysicsBox::on_destruction() {
    LOG(10) << "on_destruction";
}

void PhysicsBox::on_update() {
    LOG_DEBUG(10) << "on_update";
}

void PhysicsBox::on_fixed_update() {
    LOG_DEBUG(10) << "on_fixed_update";
}

PhysicsBox::PhysicsBox(float width, float height, bool dynamic): m_width(width), m_height(height), m_dynamic(dynamic) {

}
