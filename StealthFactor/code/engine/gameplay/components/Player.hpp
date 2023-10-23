#pragma once
#include <engine/gameplay/Component.h>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class Player : public Component
			{
			public:

				Player(Entity &entity);

				void update() override;

				bool hasJustMoved() const;

			private:

				bool justMoved{ false };
			};
		}
	}
}
