//
// Created by andrea on 6/16/19.
//

#ifndef SGE_POLYGONCOLLIDER_HPP
#define SGE_POLYGONCOLLIDER_HPP

#include "SGE/components/physics/Collider.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::cmp {
    class PolygonCollider : public Collider<PolygonCollider> {
    public:
        PolygonCollider(const utils::Handle<GameObject>& _gameobject);

        void set_path(sge::Path path);

        void visual_debug_draw_collider() override;

    protected:
        void clean_shape() override;

    private:
        Path m_path;
        Path m_world_path;
    };
}



#endif //SGE_POLYGONCOLLIDER_HPP
