#ifndef FACTORY_EXPERIMENTS_COLLIDER_HPP
#define FACTORY_EXPERIMENTS_COLLIDER_HPP

#define COLLIDER_DEFAULT_FRICTION 0.3f
#define COLLIDER_DEFAULT_RESTITUTION 0.3f
#define COLLIDER_DEFAULT_DENSITY 1.f

#include "SGE/components/Component.hpp"
#include "SGE/components/physics/Rigidbody.hpp"
#include "Box2D/Box2D.h"
#include "SGE/GameObject.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace core { class PhysicsManager; }
    namespace cmp {
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

            b2FixtureDef make_default_fixture_def() {
                b2FixtureDef def;
                def.friction = COLLIDER_DEFAULT_FRICTION;
                def.restitution = COLLIDER_DEFAULT_RESTITUTION;
                def.density = COLLIDER_DEFAULT_DENSITY;
                return def;
            }


            void update_shape(b2Shape* shape) {
                b2FixtureDef def;
                def.density = m_fixture->GetDensity();
                def.restitution = m_fixture->GetRestitution();
                def.friction = m_fixture->GetFriction();
                def.isSensor = m_fixture->IsSensor();
                m_fixture->GetBody()->DestroyFixture(m_fixture);
                def.shape = shape;
                m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
            }

            virtual void clean_shape() = 0;

            void clean_rigidbody() {
                // TODO: search for rigidbody up the hierarchy, for now just "same GameObject" is supported
                m_rigidbody = IComponent::gameobject()->template get_component<cmp::Rigidbody>("Rigidbody");
                if (m_rigidbody.is_valid()) {
                    m_dirty_rigidbody = false;
                } else {
                    LOG_ERROR << "No Rigidbody found on this gameobject";
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
        };
    }
}

#endif //FACTORY_EXPERIMENTS_COLLIDER_HPP
