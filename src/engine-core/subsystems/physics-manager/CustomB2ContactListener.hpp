#ifndef SGE_CUSTOMB2CONTACTLISTENER_HPP
#define SGE_CUSTOMB2CONTACTLISTENER_HPP

#include "Box2D/Box2D.h"
namespace sge::cmp {
    class CustomB2ContactListener : public b2ContactListener {
    public:


        void BeginContact(b2Contact *contact) override;

        void EndContact(b2Contact *contact) override;

    };
}



#endif //SGE_CUSTOMB2CONTACTLISTENER_HPP
