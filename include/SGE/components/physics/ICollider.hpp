#ifndef SGE_ICOLLIDER_HPP
#define SGE_ICOLLIDER_HPP

#include <SGE/utils/handles/Handle.hpp>
#include <SGE/GameObject.hpp>

namespace sge::cmp {
    class ICollider {
    public:
        virtual void set_density(float density) = 0;

        virtual void set_restitution(float restitution) = 0;

        virtual void set_friction(float friction) = 0;

        virtual utils::Handle<GameObject> dfsdf() = 0;
    };
}

#endif //SGE_ICOLLIDER_HPP
