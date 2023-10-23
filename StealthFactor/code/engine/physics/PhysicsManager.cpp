#include "PhysicsManager.hpp"
#include <cassert>
#include <ode/odeinit.h>
#include <ode/collision.h>

namespace engine
{
    namespace physics
    {
        PhysicsManager::Collision::Collision(dGeomID o1, dGeomID o2)
            : o1{ o1 }
            , o2{ o2 }
        {
        }

        bool PhysicsManager::setUp()
        {
            dInitODE();

            spaceId = dHashSpaceCreate(0);
            return spaceId != nullptr;
        }

        void PhysicsManager::clear()
        {
            if (spaceId != nullptr)
            {
                assert(dSpaceGetNumGeoms(spaceId) == 0);
                dSpaceDestroy(spaceId);
            }

            dCloseODE();
        }

        void PhysicsManager::update()
        {
            frameCollisions.clear();
            dSpaceCollide(spaceId, &frameCollisions, &PhysicsManager::nearCallback);
        }

        CollisionVolumeId PhysicsManager::createBoxCollision(const gameplay::Entity &entity)
        {
            auto id = dCreateBox(spaceId, 0.f, 0., 0.f);
            dGeomSetData(id, const_cast<gameplay::Entity*>(&entity));
            return id;
        }

        void PhysicsManager::destroyCollisionVolume(CollisionVolumeId id)
        {
            dGeomDestroy(id);
        }

        void PhysicsManager::setCollisionVolumePosition(CollisionVolumeId id, const sf::Vector2f& position)
        {
            dGeomSetPosition(id, position.x, position.y, 0);
        }

        void PhysicsManager::setBoxCollisionSize(CollisionVolumeId id, const sf::Vector2f& size)
        {
            assert(dGeomGetClass(id) == dBoxClass);
            dGeomBoxSetLengths(id, size.x, size.y, 1.f);
        }

        EntitySet PhysicsManager::getCollisionsWith(CollisionVolumeId id) const
        {
            EntitySet entityCollisions;

            for (auto& collision : frameCollisions)
            {
                if (collision.o1 == id)
                {
                    entityCollisions.push_back(reinterpret_cast<const gameplay::Entity*>(dGeomGetData(collision.o2)));
                }
                if (collision.o2 == id)
                {
                    entityCollisions.push_back(reinterpret_cast<const gameplay::Entity*>(dGeomGetData(collision.o1)));
                }
            }

            return entityCollisions;
        }


        void PhysicsManager::nearCallback(void* data, dGeomID o1, dGeomID o2)
        {
            auto& _frameCollisions = *reinterpret_cast<Collisions*>(data);
            _frameCollisions.emplace_back(o1, o2);
        }
    }
}