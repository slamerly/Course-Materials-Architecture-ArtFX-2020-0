#pragma once
#include <vector>
#include <ode/common.h>
#include "engine/physics/CollisionVolumeId.h"
#include <engine/physics/EntitiesCollision.h>
#include <SFML/System/Vector2.hpp>

namespace engine
{
	namespace physics
	{
		class PhysicsManager
		{
		public:

			bool setUp();

			void update();
			void clear();

			CollisionVolumeId createBoxCollision(const gameplay::Entity &entity);
			void destroyCollisionVolume(CollisionVolumeId id);

			void setCollisionVolumePosition(CollisionVolumeId id, const sf::Vector2f& position);
			void setBoxCollisionSize(CollisionVolumeId id, const sf::Vector2f& size);

			EntitySet getCollisionsWith(CollisionVolumeId id) const;

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
