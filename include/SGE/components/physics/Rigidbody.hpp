#ifndef SGE_RIGIDBODY_HPP
#define SGE_RIGIDBODY_HPP

#include "SGE/components/Component.hpp"
#include "SGE/Path.hpp"
#include "Box2D/Box2D.h"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace core {
        class PhysicsManager;
    }
    namespace cmp {

        // TODO: warning when user moves a transform when also a Dynamic or Static Rigidbody.

        /*!
         * \brief Component that model a phisically simulated object. It expects Collider components attached to the same GameObject or down the hierarchy.
         */
        class Rigidbody : public Component<Rigidbody> {
            friend class core::PhysicsManager;
        public:
            Rigidbody(const utils::Handle<GameObject>& gameobject);

            /*!
             * \brief Set the Box2D body type
             */
            void set_body_type(b2BodyType body_type);

            void set_fixed_rotation(bool fixed_rotation);

            void set_transform(const sge::Vec2<float>& position, float rotation);

            /*!
             * \brief Get the b2 body of this Rigidbody
             */
            b2Body* get_b2_body() { return m_body; }

            void destruction_callback() override;

            void apply_force(sge::Vec2<float> force_vec, sge::Vec2<float> apply_pos, bool wake);
            void apply_force_center(sge::Vec2<float> force_vec, bool wake);
            void apply_torque(float torque, bool wake);
            void apply_linear_impulse(const Vec2<float> &impulse_vec, const Vec2<float> &impulse_point, bool wake);
            void apply_angular_impulse(float impulse, bool wake);
            float get_mass();
            sge::Vec2<float> get_linear_velocity();

            std::string get_debug_string() override;

        private:
            b2Body* m_body;

            utils::event::EventHandler transform_changed_callback;
            utils::event::EventHandler parent_changed_callback;
            bool dirty_body_position_flag;

            /*!
             * \brief Updates this object's transform position and rotation accordingly to the state of the simulated body
             */
            void body_position_to_transform();

            void transform_to_body_position();
        };
    }
}

typedef utils::Handle<sge::cmp::Rigidbody> Rigidbody_H;

#endif //SGE_RIGIDBODY_HPP
