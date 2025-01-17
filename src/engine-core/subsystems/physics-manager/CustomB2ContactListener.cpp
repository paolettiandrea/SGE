#include "CustomB2ContactListener.hpp"
#include <SGE/components/physics/Collider.hpp>
#include "SGE/GameObject.hpp"

void sge::cmp::CustomB2ContactListener::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);

    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    auto col1 = (sge::cmp::Collider*)fixtureA->GetUserData();
    auto col2 = (sge::cmp::Collider*)fixtureB->GetUserData();

    b2WorldManifold world_manifold;
    contact->GetWorldManifold(&world_manifold);
    b2Vec2 vel1 = fixtureA->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );
    b2Vec2 vel2 = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );


    m_begin_collision_info_buffer.emplace_back(col1, col2, sge::Vec2<float>(vel1.x, vel1.y),
            sge::Vec2<float>(vel2.x, vel2.y));

    m_begin_collision_info_buffer.emplace_back(col2, col1, sge::Vec2<float>(vel2.x, vel2.y),
                                               sge::Vec2<float>(vel1.x, vel1.y));
}

void sge::cmp::CustomB2ContactListener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);

    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    auto col1 = (sge::cmp::Collider*)fixtureA->GetUserData();
    auto col2 = (sge::cmp::Collider*)fixtureB->GetUserData();

    b2WorldManifold world_manifold;
    contact->GetWorldManifold(&world_manifold);
    b2Vec2 vel1 = fixtureA->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );
    b2Vec2 vel2 = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );

    m_end_collision_info_buffer.emplace_back(col1, col2, sge::Vec2<float>(vel1.x, vel1.y),
                                          sge::Vec2<float>(vel2.x, vel2.y));
    m_end_collision_info_buffer.emplace_back(col2, col1, sge::Vec2<float>(vel2.x, vel2.y),
                                             sge::Vec2<float>(vel1.x, vel1.y));
}

void sge::cmp::CustomB2ContactListener::trigger_collision_callbacks() {

    for (int i = 0; i < m_begin_collision_info_buffer.size(); ++i) {
        m_begin_collision_info_buffer[i].m_my_collider->gameobject()->logichub()->on_collision_begin(m_begin_collision_info_buffer[i]);
    }

    for (int i = 0; i < m_end_collision_info_buffer.size(); ++i) {
        if (m_end_collision_info_buffer[i].m_my_collider.is_valid()) {
            auto collider_gameobject = m_end_collision_info_buffer[i].m_my_collider->gameobject();
            collider_gameobject->logichub()->on_collision_end(m_end_collision_info_buffer[i]);
        }
    }

    m_begin_collision_info_buffer.clear();
    m_end_collision_info_buffer.clear();
}

void sge::cmp::CustomB2ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    b2ContactListener::PreSolve(contact, oldManifold);
    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    auto col1 = (sge::cmp::Collider*)fixtureA->GetUserData();
    auto col2 = (sge::cmp::Collider*)fixtureB->GetUserData();

    b2WorldManifold world_manifold;
    contact->GetWorldManifold(&world_manifold);
    b2Vec2 vel1 = fixtureA->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );
    b2Vec2 vel2 = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );

    auto data1 = CollisionInfo(col1, col2, sge::Vec2<float>(vel1.x, vel1.y), sge::Vec2<float>(vel2.x, vel2.y));
    auto data2 = CollisionInfo(col2, col1, sge::Vec2<float>(vel2.x, vel2.y), sge::Vec2<float>(vel1.x, vel1.y));

    col1->gameobject()->logichub()->pre_solve(contact, oldManifold, data1);
    col2->gameobject()->logichub()->pre_solve(contact, oldManifold, data2);
}

void sge::cmp::CustomB2ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    b2ContactListener::PostSolve(contact, impulse);

    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();

    auto col1 = (sge::cmp::Collider*)fixtureA->GetUserData();
    auto col2 = (sge::cmp::Collider*)fixtureB->GetUserData();

    b2WorldManifold world_manifold;
    contact->GetWorldManifold(&world_manifold);
    b2Vec2 vel1 = fixtureA->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );
    b2Vec2 vel2 = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint(world_manifold.points[0] );

    auto data1 = CollisionInfo(col1, col2, sge::Vec2<float>(vel1.x, vel1.y), sge::Vec2<float>(vel2.x, vel2.y));
    auto data2 = CollisionInfo(col2, col1, sge::Vec2<float>(vel2.x, vel2.y), sge::Vec2<float>(vel1.x, vel1.y));


    col1->gameobject()->logichub()->post_solve(contact, impulse, data1);
    col2->gameobject()->logichub()->post_solve(contact, impulse, data2);
}

void sge::cmp::CustomB2ContactListener::clean_collision_buffers() {
    m_begin_collision_info_buffer.clear();
    m_end_collision_info_buffer.clear();
}

