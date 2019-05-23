//
// Created by andrea on 5/21/19.
//

#ifndef FACTORY_EXPERIMENTS_VERTARRAY_HPP
#define FACTORY_EXPERIMENTS_VERTARRAY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <SGE/Vec2.hpp>
#include "SGE/components/Component.hpp"


namespace sge {
    namespace core { class WindowManager; }
    namespace cmp {
        class VertArray : public Component<VertArray>, public sf::Drawable {
            friend class core::WindowManager;
        public:
            explicit VertArray(const utils::Handle<GameObject> &gameobject);

            void append_local_point(const Vec2<float>& new_local_point);
            void set_primitive(sf::PrimitiveType primitive_type);
            void set_color(sf::Color color);

            void destruction_callback() override;

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            sf::VertexArray m_vertex_array;
            std::vector<sge::Vec2<float>> m_local_points;
            utils::event::EventHandler dirty_transform_handler;

            bool is_dirty = true;
            void clean_if_dirty();

        };
    }
}


#endif //FACTORY_EXPERIMENTS_VERTARRAY_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/