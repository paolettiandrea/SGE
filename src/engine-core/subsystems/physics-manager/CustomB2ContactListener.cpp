#include "CustomB2ContactListener.hpp"
#include "Collider.hpp"
#include <stdio.h>

void sge::cmp::CustomB2ContactListener::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);

    auto col = static_cast<ICollider*>(contact->GetFixtureA()->GetUserData());
    col->set_density(20);
    //printf("%s", go->get_log_id().c_str());




}

void sge::cmp::CustomB2ContactListener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}

