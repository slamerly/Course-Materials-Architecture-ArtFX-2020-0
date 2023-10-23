#include "Player.hpp"
#include <cassert>
#include <ode/collision.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/components/BoxCollision.h>
#include <engine/gameplay/components/Target.hpp>
#include <engine/gameplay/components/Transform.h>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Player::Player(Entity &entity) : Component{ entity }
			{

			}

			void Player::update()
			{
				auto transform = getEntity().getComponent<Transform>();
				auto &inputManager = getEntity().getContext().inputManager;

				justMoved = false;
				auto position = transform->getPosition();
				float rotation = transform->getRotation();

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
					transform->setPosition(position);
					transform->setRotation(rotation);
				}

				auto collisions = getEntity().getComponent<BoxCollision>()->getCollisions();
				for (auto &entity : collisions)
				{
					auto targetComponent = entity->getComponent<Target>();
					if (targetComponent)
					{
						getEntity().getContext().entityListener.loadNextMap();
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
