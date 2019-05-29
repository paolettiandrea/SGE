//
// Created by andrea on 5/28/19.
//

#ifndef FACTORY_EXPERIMENTS_BOXCOLLIDER_HPP
#define FACTORY_EXPERIMENTS_BOXCOLLIDER_HPP

#include "SGE/components/Component.hpp"
#include "Box2D/Box2D.h"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::cmp {
    class BoxCollider : public Component<BoxCollider> {
    public:
        BoxCollider(const utils::Handle<GameObject>& gameobject);

        void initialize(float width, float height);

    private:
        b2Fixture* m_fixture;
    };
}



#endif //FACTORY_EXPERIMENTS_BOXCOLLIDER_HPP
