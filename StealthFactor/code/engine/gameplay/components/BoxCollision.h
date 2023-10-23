#pragma once
#include <ode/collision.h>
#include <SFML/System/Vector2.hpp>
#include <engine/physics/EntitiesCollision.h>
#include <engine/gameplay/Component.h>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class BoxCollision : public Component
			{
			public:

				BoxCollision(Entity& entity);
				virtual ~BoxCollision();

				void onTransformChange() override;

				void setSize(const sf::Vector2f& size);

				physics::EntitySet getCollisions() const;

			protected:

				physics::PhysicsManager& getPhysicsManager() const;

			private:

				dGeomID _collisionGeomId;
			};
		}
	}
}
