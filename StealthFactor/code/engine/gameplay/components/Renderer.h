#pragma once
#include <string>
#include <engine/graphics/ShapeListObserver.h>
#include <engine/gameplay/Component.h>
#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{

	namespace gameplay
	{
		namespace components
		{
			class Renderer : public Component
			{
			public:

				Renderer(Entity& entity);
				virtual ~Renderer();

				void onTransformChange() override;
				void setShapeListName(const std::string& name);

			protected:

				graphics::GraphicsManager& getGraphicsManager() const;

			private:

				void clear();

				graphics::ShapeListId shapeListId{};
			};
		}
	}
}
