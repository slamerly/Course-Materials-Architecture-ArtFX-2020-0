#include "Enemy.hpp"
#include <engine/gameplay/components/Player.hpp>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/EntityListener.h>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/components/Renderer.h>
#include <engine/gameplay/components/Transform.h>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Enemy::Enemy(Entity &entity) : Component{ entity }
			{

			}

			void Enemy::update()
			{
				if (_shapeListNameHasChanged)
				{
					_shapeListNameHasChanged = false;
					getEntity().getComponent<Renderer>()->setShapeListName(_shapeListName);
				}

				auto &player = getEntity().getContext().entityListener.getPlayer();
				if (player.hasJustMoved())
				{
					auto &playerPosition = player.getEntity().getComponent<Transform>()->getPosition();
					auto &myPosition = getEntity().getComponent<Transform>()->getPosition();

					auto offset = myPosition - playerPosition;
					offset /= gameplay::GameplayManager::CELL_SIZE;
					float distance2 = offset.x * offset.x + offset.y * offset.y;
					if (distance2 <= _visionRadius * _visionRadius)
					{
						if (_shootDelayCounter < _shootDelay)
						{
							++_shootDelayCounter;
						}
						else
						{
							getEntity().getContext().entityListener.gameOver();
						}
					}
					else
					{
						_shootDelayCounter = 0;
					}
				}
			}

			void Enemy::setArchetypeName(const std::string& archetypeName)
			{
				std::stringstream filename;
				filename << "archetypes/" << archetypeName << ".xml";

				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

				if (result)
				{
					assert(!doc.empty());
					auto xmlArchetype = doc.first_child();

					std::string newShapeListName = xmlArchetype.child_value("shapelist");
					if (newShapeListName != _shapeListName)
					{
						_shapeListName = newShapeListName;
						_shapeListNameHasChanged = true;
					}

					_visionRadius = std::stof(xmlArchetype.child_value("vision_radius"));
					assert(_visionRadius > 0.f);

					_shootDelay = std::stoi(xmlArchetype.child_value("shoot_delay"));
					assert(_shootDelay >= 0);
				}
				else
				{
					std::cerr << "Archetype [" << archetypeName << "] parsed with errors." << std::endl;
					std::cerr << "Error description: " << result.description() << std::endl;
					std::cerr << "Error offset: " << result.offset << std::endl;
				}
			}
		}
	}
}
