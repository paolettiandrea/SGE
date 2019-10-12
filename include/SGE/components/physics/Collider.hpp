#ifndef SGE_COLLIDER_HPP
#define SGE_COLLIDER_HPP

#define COLLIDER_DEFAULT_FRICTION 0.3f
#define COLLIDER_DEFAULT_RESTITUTION 0.3f
#define COLLIDER_DEFAULT_DENSITY 1.f

#include "SGE/components/Component.hpp"
#include "SGE/components/physics/Rigidbody.hpp"
#include "SGE/components/physics/ICollider.hpp"
#include "Box2D/Box2D.h"
#include "SGE/GameObject.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace core { class PhysicsManager; }
    namespace cmp {
        /*!
         * \brief Abstract Component that defines a phisical shape that is part of a Rigidbody
         * \tparam T The concrete Component type
         */
        template<class T>
        class Collider : public Component<T> {
            friend class core::PhysicsManager;
        public:
            Collider(const utils::Handle<GameObject>& _gameobject, const std::string& id)
                    : Component<T>(_gameobject, id) {
                clean_rigidbody();

                b2FixtureDef def;
                def.density = COLLIDER_DEFAULT_DENSITY;
                def.restitution = COLLIDER_DEFAULT_RESTITUTION;
                def.friction = COLLIDER_DEFAULT_FRICTION;

                b2CircleShape placeholder_shape;
                placeholder_shape.m_radius = 1.f;
                def.shape = &placeholder_shape;

                m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
            }

            void set_density(float density) { m_fixture->SetDensity(density); }

            void set_restitution(float restitution) { m_fixture->SetRestitution(restitution); }

            void set_friction(float friction) { m_fixture->SetFriction(friction); }


        protected:
            b2Fixture* m_fixture;
            utils::Handle<sge::cmp::Rigidbody> m_rigidbody;
            bool m_dirty_rigidbody = true;
            bool m_dirty_fixture_shape = true;


            void  set_shape(b2Shape* shape) {
                b2FixtureDef def;
                def.density = m_fixture->GetDensity();
                def.restitution = m_fixture->GetRestitution();
                def.friction = m_fixture->GetFriction();
                def.isSensor = m_fixture->IsSensor();
                m_fixture->GetBody()->DestroyFixture(m_fixture);
                def.shape = shape;
                m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
            }

            virtual void visual_debug_draw_collider() = 0;

            virtual void clean_shape() = 0;


            void clean_rigidbody() {
                m_rigidbody = find_rigidbody_upstream();
                if (m_rigidbody.is_valid()) {
                    m_dirty_rigidbody = false;
                } else {
                    LOG_ERROR << "Couldn't find a Rigidbody up the hierarchy";
                    exit(1);
                }
            }

            void clean_pass() {
                if (m_dirty_rigidbody) {
                    clean_rigidbody();
                }
                if (m_dirty_fixture_shape) {
                    clean_shape();
                }
            }

        private:
            /*!
             * \brief Methd that looks for a Rigidbody up the game hierarchy, starting from the calling GameObject
             * \return A handle to the Rigidbody if found, a null handle otherwise
             */
            utils::Handle<sge::cmp::Rigidbody> find_rigidbody_upstream() {
                auto pointed_parent_transform = this->gameobject()->transform();
                while (!pointed_parent_transform.is_null()) {
                    utils::Handle<Rigidbody> rigidbody = pointed_parent_transform->gameobject()->template get_component<Rigidbody>("Rigidbody");
                    if (rigidbody.is_valid()) return rigidbody;
                    pointed_parent_transform = pointed_parent_transform->get_parent();
                }
                return utils::Handle<Rigidbody>::null();
            }
        };

    }
}


#endif //SGE_COLLIDER_HPP
