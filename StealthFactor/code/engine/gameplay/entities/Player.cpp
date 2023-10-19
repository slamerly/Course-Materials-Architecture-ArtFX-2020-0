#include "engine/gameplay/entities/Player.hpp"

#include <cassert>
#include <ode/collision.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Target.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Player::Player(EntityContext& context)
				: Character{ context }
			{
				_shapeListId = context.graphicsManager.createShapeListInstance("player");
				assert(_shapeListId);
			}

			void Player::update()
			{
				justMoved = false;
				auto position = getPosition();
				float rotation = getRotation();

				if (context.inputManager.isKeyJustPressed(sf::Keyboard::Left))
				{
					justMoved = true;
					position.x -= gameplay::GameplayManager::CELL_SIZE;
					rotation = 180.f;
				}

				if (context.inputManager.isKeyJustPressed(sf::Keyboard::Right))
				{
					justMoved = true;
					position.x += gameplay::GameplayManager::CELL_SIZE;
					rotation = 0.f;
				}

				if (context.inputManager.isKeyJustPressed(sf::Keyboard::Up))
				{
					justMoved = true;
					position.y -= gameplay::GameplayManager::CELL_SIZE;
					rotation = -90.f;
				}

				if (context.inputManager.isKeyJustPressed(sf::Keyboard::Down))
				{
					justMoved = true;
					position.y += gameplay::GameplayManager::CELL_SIZE;
					rotation = 90.f;
				}

				if (justMoved)
				{
					setPosition(position);
					setRotation(rotation);
					propagateTransform();
				}

				auto collisions = context.physicsManager.getCollisionsWith(_collisionVolumeId);
				for (auto& entity : collisions)
				{
					auto targetEntity = dynamic_cast<entities::Target*>(entity);
					if (targetEntity)
					{
						context.entityListener.loadNextMap();
					}
				}
			}

			bool Player::hasJustMoved() const
			{
				return justMoved;
			}
		}
	}
}