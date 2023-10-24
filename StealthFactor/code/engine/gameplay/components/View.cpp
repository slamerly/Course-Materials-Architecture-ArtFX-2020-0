#include "View.h"
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
			View::View(Entity &entity) : Component{ entity }
			{
				ViewId = getGraphicsManager().createView();
			}

			View::~View()
			{
				getGraphicsManager().destroyView(ViewId);
			}

			void View::onTransformChange()
			{
				auto transform = getEntity().getComponent<Transform>();
				auto& position = transform->getPosition();
				getGraphicsManager().setViewPosition(ViewId, position);
			}

			void View::setActive()
			{
				getGraphicsManager().setViewActive(ViewId);
			}

			graphics::GraphicsManager &View::getGraphicsManager() const
			{
				return getEntity().getContext().graphicsManager;
			}
		}
	}
}
