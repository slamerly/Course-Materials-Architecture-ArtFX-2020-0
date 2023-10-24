#pragma once
#include <engine/graphics/ViewId.h>
#include <engine/gameplay/Component.h>

namespace engine
{
	namespace graphics
	{
		class GraphicsManager;
	}

	namespace gameplay
	{
		namespace components
		{
			class View : public Component
			{
			public:

				View(Entity &entity);
				virtual ~View();

				void onTransformChange() override;

				void setActive();

			protected:

				graphics::ViewId ViewId;
				graphics::GraphicsManager &getGraphicsManager() const;
			};
		}
	}
}
