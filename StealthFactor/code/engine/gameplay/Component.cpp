#include "Component.h"

namespace engine
{
	namespace gameplay
	{
		Component::Component(Entity &entity) : entity{ entity }
		{

		}

		void Component::update()
		{

		}

		void Component::onTransformChange()
		{

		}

		Entity &Component::getEntity()
		{
			return entity;
		}

		const Entity &Component::getEntity() const
		{
			return const_cast<Component*>(this)->getEntity();
		}
	}
}
