//
// Created by andrea on 5/23/19.
//

#ifndef FACTORY_EXPERIMENTS_PATHRENDERER_HPP
#define FACTORY_EXPERIMENTS_PATHRENDERER_HPP

#include <vector>
#include <SGE/Vec2.hpp>

#include "SGE/components/Component.hpp"
#include "SFML/Graphics.hpp"
#include "SGE/Path.hpp"

#include "SGE/utils/events/Events.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace core { class WindowManager; }
    namespace cmp {
        class PathRenderer : public Component<PathRenderer>, public sf::Drawable {
            friend class core::WindowManager;
        public:
            PathRenderer(const utils::Handle<GameObject> &gameobject);

            void destruction_callback() override;

            void set_path(const Path& new_path);
            void set_path_as_circle(float radius, unsigned int segments_number);

            void set_color_all(sf::Color color);



            void set_closed(bool closed);
            bool is_closed() { return m_local_path.is_closed(); }

            void set_point (unsigned int index, sge::Vec2<float> new_point);

            void set_thickness(float thickness) { m_thickness = thickness; }



        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            void elaborate_inner_point(Vec2<float> target_point, Vec2<float> prev_point, Vec2<float> next_point, sf::Vertex* vert_chunck);

            void elaborate_extremes();      // Called only at the end
            void clean_pass();


            Path m_local_path;
            Path m_world_path;
            std::vector<bool> m_dirty_world_flags;
            std::vector<bool> m_dirty_vertarray_chunk_flags;

            sf::VertexArray m_vert_array;

            sf::Color base_color = sf::Color::White;


            float m_thickness = 1;

            float m_inner_rounding_max_angle =M_PI - M_PI/16;
            utils::event::EventHandler transform_changed_evhandler;
        };
    }



}



#endif //FACTORY_EXPERIMENTS_PATHRENDERER_HPP