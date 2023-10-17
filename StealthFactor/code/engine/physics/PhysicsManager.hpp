#pragma once
#include <set>
#include <vector>
#include <ode/collision.h>
#include "engine/IManager.hpp"

namespace engine
{
	namespace physics
	{
		class PhysicsManager : public IManager
		{
		public:

			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};

			using Collisions = std::vector<Collision>;

			PhysicsManager();
			~PhysicsManager() override;

			void initialize() override;
			void update() override;
			void clear() override;

			dSpaceID getSpaceId() const;

			std::set<dGeomID> getCollisionsWith(dGeomID object) const;

		private:

			dSpaceID spaceId;
			Collisions frameCollisions;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
