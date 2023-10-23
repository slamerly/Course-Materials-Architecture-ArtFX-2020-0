#include "BoxCollision.h"
#include <cassert>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/components/Transform.h>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			BoxCollision::BoxCollision(Entity& entity) : Component{ entity }
			{
				_collisionGeomId = getPhysicsManager().createBoxCollision(getEntity());
				assert(_collisionGeomId);
			}

			BoxCollision::~BoxCollision()
			{
				getPhysicsManager().destroyCollisionVolume(_collisionGeomId);
			}

			void BoxCollision::onTransformChange()
			{
				auto transform = getEntity().getComponent<Transform>();
				auto& position = transform->getPosition();
				getPhysicsManager().setCollisionVolumePosition(_collisionGeomId, position);
			}

			void BoxCollision::setSize(const sf::Vector2f& size)
			{
				getPhysicsManager().setBoxCollisionSize(_collisionGeomId, size);
			}

			physics::EntitySet BoxCollision::getCollisions() const
			{
				return getPhysicsManager().getCollisionsWith(_collisionGeomId);
			}

			physics::PhysicsManager& BoxCollision::getPhysicsManager() const
			{
				return getEntity().getContext().physicsManager;
			}
		}
	}
}
