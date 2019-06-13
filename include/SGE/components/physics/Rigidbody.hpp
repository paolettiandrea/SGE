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
        class Rigidbody : public Component<Rigidbody> {
            friend class core::PhysicsManager;
        public:
            Rigidbody(const utils::Handle<GameObject>& gameobject);

            void set_body_type(b2BodyType body_type);


            b2Body* get_b2_body() { return m_body; }

            void destruction_callback() override;

        private:
            b2Body* m_body;

            void update_transform();
        };
    }
}



#endif //SGE_RIGIDBODY_HPP
