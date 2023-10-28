#include "Prefab.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/components/BoxCollision.h>
#include <engine/gameplay/components/Enemy.hpp>
#include <engine/gameplay/components/View.h>
#include <engine/gameplay/components/Player.hpp>
#include <engine/gameplay/components/Renderer.h>
#include <engine/gameplay/components/Target.hpp>
#include <engine/gameplay/components/Transform.h>

namespace engine
{
	namespace gameplay
	{
		Prefab::Prefab(const std::string& name) : _name{ name }
		{

		}

		std::unique_ptr<Entity> Prefab::instantiate(EntityContext& context) const
		{
			std::unique_ptr<Entity> entity;

			std::stringstream filename;
			filename << "prefabs/" << _name << ".xml";

			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

			if (result)
			{
				assert(!doc.empty());
				auto xmlMap = doc.first_child();

				entity.reset(new Entity{ context });

				std::cout << _name << ": " << std::endl;

				entity->addComponent<components::Transform>();

				for (auto& xmlElement : xmlMap.child("components").children())
				{
					if (!std::strcmp(xmlElement.name(), "view"))
					{
						entity->addComponent<components::View>();
						std::cout << "	" << "View" << std::endl;
					}
					else if (!std::strcmp(xmlElement.name(), "collision_box"))
					{
						auto& collisionBox = entity->addComponent<components::BoxCollision>();

						float width = std::stof(xmlElement.child_value("width"));
						float height = std::stof(xmlElement.child_value("height"));

						collisionBox.setSize(sf::Vector2f{ width, height });
						std::cout << "	" << "collision_box" << std::endl;
					}

					else if (!std::strcmp(xmlElement.name(), "enemy"))
					{
						auto& enemy = entity->addComponent<components::Enemy>();

						std::string archetype = xmlElement.child_value("archetype");

						enemy.setArchetypeName(archetype);
						std::cout << "	" << "enemy" << std::endl;
					}

					else if (!std::strcmp(xmlElement.name(), "player"))
					{
						entity->addComponent<components::Player>();
						std::cout << "	" << "player" << std::endl;
					}

					else if (!std::strcmp(xmlElement.name(), "renderer"))
					{
						auto& renderer = entity->addComponent<components::Renderer>();

						std::string shapelist = xmlElement.child_value("shapelist");

						renderer.setShapeListName(shapelist);
						std::cout << "	" << "renderer" << std::endl;
					}

					else if (!std::strcmp(xmlElement.name(), "target"))
					{
						entity->addComponent<components::Target>();
						std::cout << "	" << "target" << std::endl;
					}

					else
					{
						std::cerr << "Unknown component  [" << xmlElement.name() << "]." << std::endl;
						std::cout << "	" << "unknow" << std::endl;
					}
				}
			}
			else
			{
				std::cerr << "Prefab [" << _name << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}

			return entity;
		}
	}
}
