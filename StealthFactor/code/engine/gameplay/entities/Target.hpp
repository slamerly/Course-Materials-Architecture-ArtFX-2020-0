#pragma once
#include <engine/gameplay/Entity.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Target : public Entity
			{
			public:
				Target();
				~Target();

				virtual void update();
			};
		}
	}
}
