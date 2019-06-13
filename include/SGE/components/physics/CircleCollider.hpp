//
// Created by andrea on 6/2/19.
//

#ifndef SGE_CIRCLECOLLIDER_HPP
#define SGE_CIRCLECOLLIDER_HPP

#include "SGE/components/physics/Collider.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace cmp {
        class CircleCollider : public Collider<CircleCollider>  {
        public:
            CircleCollider(const utils::Handle<GameObject>& gameobject);

            void set_radius(float radius);
            float get_radius();

        protected:
            void clean_shape() override;

        private:
            float m_radius;
        };
    }
}



#endif //SGE_CIRCLECOLLIDER_HPP
