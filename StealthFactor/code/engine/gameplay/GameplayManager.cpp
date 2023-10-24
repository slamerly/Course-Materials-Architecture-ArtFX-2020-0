#include "engine/gameplay/GameplayManager.hpp"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/Prefab.h>
#include <engine/gameplay/components/View.h>
#include <engine/gameplay/components/Transform.h>
#include <engine/gameplay/components/Player.hpp>

namespace engine
{
	namespace gameplay
	{
		const float GameplayManager::CELL_SIZE = 50.f;

		GameplayManager::GameplayManager(graphics::GraphicsManager& graphicsManager, input::InputManager& inputManager, physics::PhysicsManager& physicsManager) : _context{ graphicsManager, inputManager, physicsManager, *this }
		{

		}

		void GameplayManager::setUp()
		{

		}

		void GameplayManager::clear()
		{
			removeEntities();
		}

		void GameplayManager::update()
		{
			for (auto& entity : _entities)
			{
				entity->update();
			}

			_preventMapCompletion = false;
			if (_nextMapRequested && !_nextMapName.empty())
			{
				_nextMapRequested = false;
				loadMap(_nextMapName);
			}
		}

		void GameplayManager::loadMap(const std::string& mapName)
		{
			removeEntities();

			std::stringstream filename;
			filename << "maps/" << mapName << ".xml";

			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

			if (result)
			{
				assert(!doc.empty());
				auto xmlMap = doc.first_child();

				_rows = std::stoi(xmlMap.child_value("rows"));
				assert(_rows >= 0);

				_columns = std::stoi(xmlMap.child_value("columns"));
				assert(_columns >= 0);

				for (auto& xmlElement : xmlMap.child("elements").children())
				{
					std::string prefabName;

					if (!std::strcmp(xmlElement.name(), "enemy"))
					{
						prefabName = xmlElement.child_value("prefab");
					}
					else if (!std::strcmp(xmlElement.name(), "player"))
					{
						prefabName = "player";
					}
					else if (!std::strcmp(xmlElement.name(), "target"))
					{
						prefabName = "target";
					}
					else
					{
						std::cerr << "Unknown prefab  [" << xmlElement.name() << "]." << std::endl;
						continue;
					}

					std::unique_ptr<Prefab> prefab{ new Prefab{ prefabName} };
					auto entity = prefab->instantiate(_context);

					if (entity)
					{
						auto transform = entity->getComponent<components::Transform>();

						int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < _rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < _columns);

						transform->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						auto player = entity->getComponent<components::Player>();
						if (player)
						{
							playerComponent = player;
						}

						_entities.insert(std::move(entity));
					}
					else
					{
						std::cerr << "Prefab [" << prefabName << "] instantiated no entity." << std::endl;
					}
				}

				std::unique_ptr<Prefab> ViewPrefab{ new Prefab{ "View" } };
				auto ViewEntity = ViewPrefab->instantiate(_context);
				ViewEntity->getComponent<components::View>()->setActive();
				ViewEntity->getComponent<components::Transform>()->setPosition(sf::Vector2f{ _columns * (CELL_SIZE / 2.f), _rows * (CELL_SIZE / 2.f) });
				_entities.insert(std::move(ViewEntity));

				_currentMapName = mapName;
				_nextMapName = xmlMap.child_value("next_map");

				// JIRA-1337: Map is skipped.
				// This prevents the map to be completed during the first frame. I don't know why this happens.
				_preventMapCompletion = true;
			}
			else
			{
				std::cerr << "Map [" << mapName << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}
		}

		void GameplayManager::gameOver()
		{
			std::cout << "Game over" << std::endl;
			loadMap(_currentMapName);
		}

		void GameplayManager::loadNextMap()
		{
			if (!_preventMapCompletion)
			{
				_nextMapRequested = true;
			}
		}

		const components::Player &GameplayManager::getPlayer() const
		{
			assert(playerComponent);
			return *playerComponent;
		}

		void GameplayManager::removeEntities()
		{
			_entities.clear();
			playerComponent = nullptr;
		}
	}
}