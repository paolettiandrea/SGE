#ifndef SGE_COLLIDER_HPP
#define SGE_COLLIDER_HPP


#ifndef SGE_COLLIDER_DEFAULT_DENSITY
#define SGE_COLLIDER_DEFAULT_DENSITY 1.f
#endif

#ifndef SGE_COLLIDER_DEFAULT_RESTITUTION
#define SGE_COLLIDER_DEFAULT_RESTITUTION 0.3
#endif

#ifndef SGE_COLLIDER_DEFAULT_FRICTION
#define SGE_COLLIDER_DEFAULT_FRICTION 1.f
#endif

#include <SGE/utils/handles/Handle.hpp>
#include "Box2D/Box2D.h"
#include "SGE/components/Component.hpp"
#include "SGE/Path.hpp"
#include "Rigidbody.hpp"
#include "CollisionInfo.hpp"

namespace sge {
    namespace core {class PhysicsManager;  }
    namespace cmp {


        class Collider : public Component<Collider> {
            friend class core::PhysicsManager;
        public:
            explicit Collider(const utils::Handle<GameObject>& _gameobject);

            enum ColliderType {Polygon, Circle, Chain};

            void set_as_polygon(sge::Path path);

            void set_as_chain(sge::Path path);

            void set_as_circle(float radius);

            void visual_debug_draw_collider();




            void reallocation_callback() override;

            void load_spath(const std::string& filaname);

            utils::Handle<sge::cmp::Rigidbody> get_rigidbody();

            void set_sensor(bool is_sensor);
            bool is_sensor();

            void set_density(float density);
            void set_friction(float friction);
            void sed_restitution(float restitution);

            void destruction_callback() override;


        protected:
            b2Fixture* m_fixture;
            utils::Handle<sge::cmp::Rigidbody> m_rigidbody;
            bool m_dirty_rigidbody = true;
            bool m_dirty_fixture_shape = true;
            float m_radius;

            utils::event::EventHandler relative_transform_changed_event;
            utils::event::EventHandler relative_hierarchy_changed_event;
            /*!
             * \brief Vector containing all the transforms from this gameobject's (included)
             * to the gameobject containing the Rigidbody upstream (excluded)
             */
            std::vector<utils::Handle<sge::cmp::Transform>> relative_hierarchy_vector;


            void clean_shape();

            void set_shape(b2Shape* shape);

            b2FixtureDef clone_fixture_def(b2Fixture* fixture);


            void clean_rigidbody();

            void clean_pass();


        private:
            Path m_path;
            Path m_relative_path;

            ColliderType m_type;

            /*!
            * \brief Updates the upstream references (meaning the handle to the Rigidbody and the vector of handles
             * that keeps track of all the hierarchy to the rigidbody)
            */
            void update_upstream_handles();

            void update_relative_path();
        };
    }
}



#endif //SGE_COLLIDER_HPP
