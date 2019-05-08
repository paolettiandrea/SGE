//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_POLYGON_HPP
#define FACTORY_EXPERIMENTS_POLYGON_HPP

#include "SGE/components/Component.hpp"
#include <vector>
#include "SGE/Vec2.hpp"
#include "SFML/Graphics.hpp"

namespace sge::core { class WindowManager; }

namespace sge::cmp {
    /*!
     * \brief Probably Shape would be a better name (?)
     */
class Polygon : public Component<Polygon>, public sf::Drawable {
    public:
        Polygon(const utils::Handle<GameObject> &gameobject);

        void set_polygon(float radius, int vertices_number);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
        sf::VertexArray m_vertex_array;
        sf::Transform m_gap_transform;

        unsigned int m_vert_number = 0;

        void update_gap_transform();

        friend class core::WindowManager;
    };
}


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/




#endif //FACTORY_EXPERIMENTS_POLYGON_HPP
