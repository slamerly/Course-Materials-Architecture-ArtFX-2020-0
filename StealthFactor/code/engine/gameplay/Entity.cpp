#include "Entity.hpp"

namespace engine
{
	namespace gameplay
	{
		Entity::Entity()
		{
		}

		Entity::~Entity()
		{
			dGeomDestroy(collisionGeomId);
		}

		void Entity::update()
		{
		}

		void Entity::draw()
		{
			graphics::Manager::getInstance().draw(shapeList, getTransform());
		}

		const sf::Vector2f & Entity::getPosition() const
		{
			return _position;
		}

		void Entity::setPosition(const sf::Vector2f &newPosition)
		{
			_position = newPosition;
			updateTransform();
		}

		float Entity::getRotation() const
		{
			return _rotation;
		}

		void Entity::setRotation(float newRotation)
		{
			_rotation = newRotation;
			updateTransform();
		}

		const sf::Transform & Entity::getTransform() const
		{
			return _transform;
		}

		const graphics::ShapeList& Entity::getShapeList()
		{
			return shapeList;
		}

		void Entity::updateTransform()
		{
			_transform = sf::Transform::Identity;
			_transform.translate(_position);
			_transform.rotate(_rotation);
		}
	}
}
