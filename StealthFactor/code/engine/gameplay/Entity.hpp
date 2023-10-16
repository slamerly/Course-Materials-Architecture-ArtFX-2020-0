#pragma once

#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/GameplayManager.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity
		{
		public:
			Entity();
			virtual ~Entity();

			virtual void update();
			virtual void draw();

			const sf::Vector2f &getPosition() const;
			void setPosition(const sf::Vector2f &newPosition);

			float getRotation() const;
			void setRotation(float newRotation);

			const sf::Transform &getTransform() const;

		protected:
			graphics::ShapeList shapeList;
			dGeomID collisionGeomId;

		private:
			sf::Vector2f _position{};
			float _rotation{ 0.f };
			sf::Transform _transform;

			void updateTransform();
		};
	}
}