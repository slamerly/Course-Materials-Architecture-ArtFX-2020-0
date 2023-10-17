#include "PhysicsManager.hpp"
#include <ode/odeinit.h>

namespace engine
{
	namespace physics
	{
		PhysicsManager::Collision::Collision(dGeomID o1, dGeomID o2)
			: o1{ o1 }
			, o2{ o2 }
		{
		}

		PhysicsManager::PhysicsManager()
		{
			dInitODE();

			spaceId = dHashSpaceCreate(0);
		}

		PhysicsManager::~PhysicsManager()
		{
			dSpaceDestroy(spaceId);
			dCloseODE();
		}

		void initialize()
		{
		}

		void PhysicsManager::initialize()
		{
		}

		void PhysicsManager::update()
		{
			frameCollisions.clear();
			dSpaceCollide(spaceId, &frameCollisions, &PhysicsManager::nearCallback);
		}

		void PhysicsManager::clear()
		{
		}

		dSpaceID PhysicsManager::getSpaceId() const
		{
			return spaceId;
		}

		std::set<dGeomID> PhysicsManager::getCollisionsWith(dGeomID object) const
		{
			std::set<dGeomID> objectCollisions;

			for (auto &collision : frameCollisions)
			{
				if (collision.o1 == object)
				{
					objectCollisions.insert(collision.o2);
				}
				if (collision.o2 == object)
				{
					objectCollisions.insert(collision.o1);
				}
			}

			return objectCollisions;
		}

		void PhysicsManager::nearCallback(void *data, dGeomID o1, dGeomID o2)
		{
			auto &frameCollisions = *reinterpret_cast<Collisions *>(data);
			frameCollisions.emplace_back(o1, o2);
		}
	}
}
