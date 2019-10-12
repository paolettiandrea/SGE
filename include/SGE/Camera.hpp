#ifndef SGE_CAMERA_HPP
#define SGE_CAMERA_HPP

#include "SFML/Graphics.hpp"


namespace sge {
    namespace core { class WindowManager;}
    /*!
     * \brief Manages the point of view of the player
     * \details
     * Wraps around an sf::View object
     */
    class Camera {
    friend class core::WindowManager;
    public:
        explicit Camera(float vertical_size = 200);
        void set_zoom(float vertical_size);
        void offset_zoom(float vertical_size_offset);
        float get_zoom();


        float get_ratio() { return m_screen_ratio; }
        float get_vertical_size() { return m_vertical_size; }

        void set_center(float x, float y);
        void offset_center(float x_offset, float y_offset);


        const sf::View &get_view() const;

    private:
        sf::View m_view;
        float m_screen_ratio;
        float m_vertical_size;
        bool changed_view_flag = true;

        void update_view_size();
        void set_ratio(float screen_ratio);
    };
}



#endif //SGE_CAMERA_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/