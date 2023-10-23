#include "Renderer.h"
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/components/Transform.h>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Renderer::Renderer(Entity& entity) : Component{ entity }
			{

			}

			Renderer::~Renderer()
			{
				clear();
			}

			void Renderer::onTransformChange()
			{
				if (shapeListId)
				{
					auto transform = getEntity().getComponent<Transform>();
					getGraphicsManager().setShapeListInstanceMatrix(shapeListId, transform->getMatrix());
				}
			}

			void Renderer::setShapeListName(const std::string& name)
			{
				clear();

				if (!name.empty())
				{
					shapeListId = getGraphicsManager().createShapeListInstance(name);
					onTransformChange();
				}
			}

			void Renderer::clear()
			{
				if (shapeListId)
				{
					getGraphicsManager().destroyShapeListInstance(shapeListId);
					shapeListId = 0;
				}
			}

			graphics::GraphicsManager& Renderer::getGraphicsManager() const
			{
				return getEntity().getContext().graphicsManager;
			}
		}
	}
}
