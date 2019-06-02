#ifndef FACTORY_EXPERIMENTS_BOXCOLLIDER_HPP
#define FACTORY_EXPERIMENTS_BOXCOLLIDER_HPP

#include "SGE/components/Component.hpp"
#include "SGE/components/physics/Collider.hpp"
#include "Box2D/Box2D.h"


namespace sge::cmp {
    class BoxCollider : public Collider<BoxCollider> {
    public:
        BoxCollider(const utils::Handle<GameObject>& gameobject);

        float get_width();
        void set_width(float width);

        float get_height();
        void set_height(float height);

    protected:
        void clean_shape() override;

    private:
        float m_width = 1.f;
        float m_height = 1.f;
    };
}

#endif //FACTORY_EXPERIMENTS_BOXCOLLIDER_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/