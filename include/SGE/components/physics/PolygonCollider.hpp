//
// Created by andrea on 6/16/19.
//

#ifndef SGE_POLYGONCOLLIDER_HPP
#define SGE_POLYGONCOLLIDER_HPP


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


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace core {class PhysicsManager;  }
    namespace cmp {
        class PolygonCollider : public Component<PolygonCollider> {
            friend class core::PhysicsManager;
        public:
            explicit PolygonCollider(const utils::Handle<GameObject>& _gameobject);

            void set_path(sge::Path path);

            void visual_debug_draw_collider();


            void  set_shape(b2Shape* shape);

            void reallocation_callback() override;

        protected:
            b2Fixture* m_fixture;
            utils::Handle<sge::cmp::Rigidbody> m_rigidbody;
            bool m_dirty_rigidbody = true;
            bool m_dirty_fixture_shape = true;


            void clean_shape();



            b2FixtureDef clone_fixture_def(b2Fixture* fixture);


            void clean_rigidbody();

            void clean_pass();


        private:
            Path m_path;
            Path m_world_path;

            /*!
            * \brief Method that looks for a Rigidbody up the game hierarchy, starting from the calling GameObject
            * \return A handle to the Rigidbody if found, a null handle otherwise
            */
            utils::Handle<sge::cmp::Rigidbody> find_rigidbody_upstream();
        };
    }
}



#endif //SGE_POLYGONCOLLIDER_HPP
