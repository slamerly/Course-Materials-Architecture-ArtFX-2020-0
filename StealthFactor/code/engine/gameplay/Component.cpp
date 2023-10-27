#include "Component.h"

namespace engine
{
	namespace gameplay
	{
		Component::Component(Entity &entityp) : _entity{ entityp }
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
			return _entity;
		}

		const Entity &Component::getEntity() const
		{
			return const_cast<Component*>(this)->getEntity();
		}
	}
}
