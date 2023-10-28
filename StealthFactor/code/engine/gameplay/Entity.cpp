#include "Entity.hpp"
#include <engine/gameplay/Component.h>

namespace engine
{
	namespace gameplay
	{
		Entity::Entity(EntityContext& context) : context{ context }
		{
		}

		void Entity::update()
		{
			for (auto &component : components)
			{
				//
				component->update();
			}
		}

		void Entity::onTransformChange()
		{
			for (auto &component : components)
			{
				component->onTransformChange();
			}
		}

		EntityContext &Entity::getContext()
		{
			return context;
		}

		const EntityContext &Entity::getContext() const
		{
			return const_cast<Entity *>(this)->getContext();
		}
	}
}
