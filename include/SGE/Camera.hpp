#ifndef FACTORY_EXPERIMENTS_CAMERA_HPP
#define FACTORY_EXPERIMENTS_CAMERA_HPP

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
        explicit Camera(float screen_ratio, float vertical_size = 200);
        void set_zoom(float vertical_size);
        void add_zoom(float vertical_size_offset);
        void set_ratio(float screen_ratio);

        float get_ratio() { return m_screen_ratio; }
        float get_vertical_size() { return m_vertical_size; }



        const sf::View &get_view() const;

    private:
        sf::View m_view;
        float m_screen_ratio;
        float m_vertical_size;
        bool changed_view_flag = true;

        void update_view_size();
    };
}



#endif //FACTORY_EXPERIMENTS_CAMERA_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/