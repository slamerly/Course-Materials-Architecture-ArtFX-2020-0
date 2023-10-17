#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>


namespace engine
{
	Engine *Engine::instance = nullptr;

	void Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			startMap = configuration.child_value("start_map");
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;
		}
	}

	void Engine::run()
	{
		running = true;

		gameplayM.loadMap(startMap);

		sf::Clock clock;
		while (running)
		{
			deltaTime = clock.restart().asSeconds();

			physicsM.update();
			gameplayM.update();

			graphicsM.clear();

			//graphicsM.draw();

			graphicsM.display();

			inputM.clear();

			sf::Event event;
			while (graphicsM.getWindow().pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					getInstance().exit();
					break;

				case sf::Event::KeyPressed:
					inputM.onKeyPressed(event.key);
					break;

				case sf::Event::KeyReleased:
					inputM.onKeyReleased(event.key);
					break;

				default:
					break;
				}
			}
		}
	}

	float Engine::getDeltaTime() const
	{
		return deltaTime;
	}

	void Engine::exit()
	{
		running = false;
	}

	Engine &Engine::getInstance()
	{
		if (!instance)
			instance = new Engine();

		return *instance;
	}
}
