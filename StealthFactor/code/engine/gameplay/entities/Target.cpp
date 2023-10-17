#include "Target.hpp"
#include <engine/gameplay/GameplayManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Target::Target()
			{
				shapeList.load("target");
				physics::PhysicsManager physicsManager = physics::PhysicsManager();

				collisionGeomId = dCreateBox(physicsManager.getSpaceId(), gameplay::GameplayManager::CELL_SIZE * 0.9f, gameplay::GameplayManager::CELL_SIZE * 0.9f, 1.f);
				dGeomSetData(collisionGeomId, this);
			}

			Target::~Target()
			{
				dGeomDestroy(collisionGeomId);
			}

			void Target::update()
			{
				auto &position = getPosition();
				dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
			}
		}
	}
}
