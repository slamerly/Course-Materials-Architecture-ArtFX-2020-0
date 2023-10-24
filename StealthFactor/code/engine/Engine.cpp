#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>


namespace engine
{
	Engine::Engine() : gameplayM{ graphicsM, inputM, physicsM }, graphicsM{ *this }
	{

	}

	bool Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			startMap = configuration.child_value("start_map");

			return true;
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;

			return false;
		}
	}

	bool Engine::setUp()
	{
		if (!graphicsM.setUp())
		{
			return false;
		}

		if (!physicsM.setUp())
		{
			return false;
		}

		gameplayM.setUp();

		return true;
	}

	void Engine::clear()
	{
		gameplayM.clear();
		physicsM.clear();
		graphicsM.clear();
	}

	void Engine::run()
	{
		running = true;

		gameplayM.loadMap(startMap);

		sf::Clock clock;
		while (running)
		{
			deltaTime = clock.restart().asSeconds();

			inputM.clear();

			physicsM.update();
			graphicsM.pollEvent();
			gameplayM.update();

			graphicsM.draw();
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

	void Engine::onEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			running = false;
			break;

		case sf::Event::LostFocus:
			inputM.setActive(false);
			break;

		case sf::Event::GainedFocus:
			inputM.setActive(true);
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