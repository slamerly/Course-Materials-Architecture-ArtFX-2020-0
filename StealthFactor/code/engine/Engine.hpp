#pragma once
#include <string>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/EventListener.h>

namespace engine
{
	class Engine : public EventListener
	{
	public:

		Engine();

		bool loadConfiguration();

		bool setUp();
		void clear();

		void run();
		float getDeltaTime() const;

		void exit();

		void onEvent(const sf::Event &event) override;

	private:

		gameplay::GameplayManager gameplayM;
		graphics::GraphicsManager graphicsM;
		physics::PhysicsManager physicsM;
		input::InputManager inputM;
		
		bool running;
		float deltaTime;

		// Configuration
		std::string startMap;
	};
}
