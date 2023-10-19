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

        CollisionVolumeId PhysicsManager::createCollisionBox(gameplay::Entity* entity, float width, float height)
        {
            auto id = dCreateBox(spaceId, width, height, 1.f);
            dGeomSetData(id, entity);
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

        std::set<gameplay::Entity*> PhysicsManager::getCollisionsWith(CollisionVolumeId id) const
        {
            std::set<gameplay::Entity*> entityCollisions;

            for (auto& collision : frameCollisions)
            {
                if (collision.o1 == id)
                {
                    entityCollisions.insert(reinterpret_cast<gameplay::Entity*>(dGeomGetData(collision.o2)));
                }
                if (collision.o2 == id)
                {
                    entityCollisions.insert(reinterpret_cast<gameplay::Entity*>(dGeomGetData(collision.o1)));
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