#ifndef SGE_PATHDEBUGSHAPE_HPP
#define SGE_PATHDEBUGSHAPE_HPP

#include "DebugShape.hpp"
#include "SGE/Path.hpp"
#include "PointDebugShape.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::debug {
    class PathDebugShape : public sge::debug::DebugShape {
    public:
    PathDebugShape(sge::Path path, float duration, const std::string& label, unsigned int decimals, sf::Color color=SGE_DEFAULT_DEBUG_COLOR)
    : DebugShape(duration), lines_vert_array(sf::PrimitiveType::LineStrip) {

        for (int i = 0; i < path.get_size(); ++i) {
            lines_vert_array.append(sf::Vertex(sf::Vector2f(path[i].x,-path[i].y),color));
            std::string point_label;
            if (i==0) point_label = label;
            point_debug_shapes.emplace_back(path[i].x, path[i].y,duration,point_label,decimals);
        }
        if (path.is_closed()) lines_vert_array.append(sf::Vertex(sf::Vector2f(path[0].x,-path[0].y)));
    }

    void update_dimensions(float vertical_view_size) override;

    protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void internal_initialization(const sf::Font& debug_font) override;

    private:
    std::vector<sge::debug::PointDebugShape> point_debug_shapes;
    sf::VertexArray lines_vert_array;
};

}


#endif //SGE_PATHDEBUGSHAPE_HPP
