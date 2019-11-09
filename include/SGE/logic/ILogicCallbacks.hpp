#ifndef SGE_ILOGICCALLBACKS_HPP
#define SGE_ILOGICCALLBACKS_HPP

#include "SGE/components/physics/CollisionInfo.hpp"
#include "Box2D/Box2D.h"

namespace sge {
    /*!
 * \brief Interface that contains all the callback that a Logic object can have.
 */
    struct ILogicCallbacks {
        /*!
         * \brief Callback guaranteed to be called after attachment and before any update or fixed_update
         */
        virtual void on_start() = 0;
        /*!
         * \brief Calback guaranteed to be called before destruction of the object this object is attached to
         */
        virtual void on_destruction() = 0;

        /*!
         * \brief Callbacks called right before render
         */
        virtual void on_update() = 0;
        /*!
         * \brief Callback called right before a physics update
         * \details
         *  Could happen 0, 1 or multiple times in a game_loop pass depending on the relation between delta_time and fixed_delta_time
         */
        virtual void on_fixed_update() = 0;

        virtual void on_collision_begin(CollisionInfo &collision_info) = 0;
        virtual void on_collision_end(CollisionInfo &collision_info) = 0;

        virtual void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const CollisionInfo &info) = 0;
        virtual void post_solve(b2Contact *contact, const b2ContactImpulse *impulse, const CollisionInfo &info) = 0;

    };
}


#endif //SGE_ILOGICCALLBACKS_HPP
