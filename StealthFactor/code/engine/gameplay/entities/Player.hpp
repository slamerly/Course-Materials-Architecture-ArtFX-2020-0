#pragma once
#include <engine/gameplay/Entity.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Player : public Entity
			{
			public:
				Player();

				virtual void update();

				bool hasJustMoved() const;

			private:
				bool justMoved{ false };
			};
		}
	}
}
