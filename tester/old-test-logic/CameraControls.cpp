#include "CameraControls.hpp"

std::string CameraControls::get_logic_type_id() {
    return "CameraControls";
}

void CameraControls::on_update() {
    Logic::on_update();

    float delta_time = env()->delta_time();

    float zoom_dependernt_zoom_speed = zoom_speed*scene()->get_camera()->get_zoom()*delta_time;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        scene()->get_camera()->offset_zoom(zoom_dependernt_zoom_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
        scene()->get_camera()->offset_zoom(-zoom_dependernt_zoom_speed);
    }

    float zoom_dependent_lateral_speed = lateral_speed*scene()->get_camera()->get_zoom()*delta_time;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        scene()->get_camera()->offset_center(-zoom_dependent_lateral_speed,0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        scene()->get_camera()->offset_center(zoom_dependent_lateral_speed,0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        scene()->get_camera()->offset_center(0,-zoom_dependent_lateral_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        scene()->get_camera()->offset_center(0,zoom_dependent_lateral_speed);
    }
}
