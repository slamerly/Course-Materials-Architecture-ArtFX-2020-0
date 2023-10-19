#pragma once
#include <set>
#include <vector>
#include <ode/common.h>
#include "engine/physics/CollisionVolumeId.h"
#include <SFML/System/Vector2.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;
	}

	namespace physics
	{
		class PhysicsManager
		{
		public:
			bool setUp();

			void update();
			void clear();

			std::set<gameplay::Entity*> getCollisionsWith(CollisionVolumeId id) const;

			CollisionVolumeId createCollisionBox(gameplay::Entity* entity, float width, float height);
			void destroyCollisionVolume(CollisionVolumeId id);

			void setCollisionVolumePosition(CollisionVolumeId id, const sf::Vector2f& position);

		private:

			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};
			using Collisions = std::vector<Collision>;

			dSpaceID spaceId{};
			Collisions frameCollisions;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
