#pragma once

#include <engine/graphics/ShapeListObserver.h>
#include <engine/gameplay/Entity.hpp>
#include <engine/physics/CollisionVolumeId.h>
#include <ode/collision.h>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Target : public Entity
			{
			public:
				Target(EntityContext &contextp);
				~Target();

				virtual void update() override;

				void propagateTransform();

			private:
				graphics::ShapeListId shapeListId;
				physics::CollisionVolumeId collisionVolumeId;
			};
		}
	}
}
