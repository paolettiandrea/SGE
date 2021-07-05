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

            /*!
             * \brief Get the body type of this Rigidbody
             */
            b2Body* get_b2_body() { return m_body; }

            void destruction_callback() override;

        private:
            b2Body* m_body;

            /*!
             * \brief Updates this object's transform position and rotation accordingly to the state of the simulated body
             */
            void update_transform();
        };
    }
}



#endif //SGE_RIGIDBODY_HPP
