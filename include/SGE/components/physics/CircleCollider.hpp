//
// Created by andrea on 6/2/19.
//

#ifndef SGE_CIRCLECOLLIDER_HPP
#define SGE_CIRCLECOLLIDER_HPP

#include "SGE/components/physics/Collider.hpp"

namespace sge {
    namespace cmp {
        class CircleCollider : public Collider<CircleCollider>  {
        public:
            CircleCollider(const utils::Handle<GameObject>& gameobject);

            void set_radius(float radius);
            float get_radius();

            void set_center_offset(sge::Vec2<float> new_pos);
            sge::Vec2<float> get_center_offset();

            void visual_debug_pass() override;

        protected:
            void clean_shape() override;

        private:
            float m_radius;
            sge::Vec2<float> m_local_center_offset = sge::Vec2<float>();
        };
    }
}

#endif //SGE_CIRCLECOLLIDER_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/