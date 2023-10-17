#include "engine/gameplay/entities/Player.hpp"
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Target.hpp>
#include <engine/input/InputManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			physics::PhysicsManager physicsManager = physics::PhysicsManager();
			gameplay::GameplayManager gameplayManager = gameplay::GameplayManager();
			input::InputManager inputManager = input::InputManager();

			Player::Player()
			{
				shapeList.load("player");
				collisionGeomId = dCreateBox(physicsManager.getSpaceId(), gameplay::GameplayManager::CELL_SIZE * 0.9f, gameplay::GameplayManager::CELL_SIZE * 0.9f, 1.f);
				dGeomSetData(collisionGeomId, this);
			}

			void Player::update()
			{
				justMoved = false;
				sf::Vector2f position = getPosition();
				float rotation = getRotation();

				if (inputManager.isKeyJustPressed(sf::Keyboard::Left))
				{
					justMoved = true;
					position.x -= gameplay::GameplayManager::CELL_SIZE;
					rotation = 180.f;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Right))
				{
					justMoved = true;
					position.x += gameplay::GameplayManager::CELL_SIZE;
					rotation = 0.f;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Up))
				{
					justMoved = true;
					position.y -= gameplay::GameplayManager::CELL_SIZE;
					rotation = -90.f;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Down))
				{
					justMoved = true;
					position.y += gameplay::GameplayManager::CELL_SIZE;
					rotation = 90.f;
				}

				if (justMoved)
				{
					setPosition(position);
					setRotation(rotation);

					dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
				}
				
				auto collisions = physicsManager.getCollisionsWith(collisionGeomId);
				for (auto &geomId : collisions)
				{
					auto entity = reinterpret_cast<Entity *>(dGeomGetData(geomId));
					auto targetEntity = dynamic_cast<entities::Target *>(entity);
					if (targetEntity)
					{
						gameplayManager.loadNextMap();
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
