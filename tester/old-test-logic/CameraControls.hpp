#ifndef SGE_CAMERACONTROLS_HPP
#define SGE_CAMERACONTROLS_HPP


#include <SGE/logic/Logic.hpp>

/**
 * \brief Logic that allows for easy control of a Camera in a Scene by keyboard
 */
class CameraControls : public sge::Logic {
public:
    /**
     * Contructs a CameraControls Logic object, that controls the Camera of the Scene it's in
     * @param zoom_speed A factor that defines the zoom speed
     * @param lateral_speed A factor that defines the lateral speed
     */
    CameraControls(float zoom_speed, float lateral_speed){
        this->lateral_speed = lateral_speed;
        this->zoom_speed = zoom_speed;
    }

    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

private:
    float zoom_speed;
    float lateral_speed;
};


#endif //SGE_CAMERACONTROLS_HPP
