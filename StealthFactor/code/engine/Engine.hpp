#pragma once
#include <string>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/IManager.hpp >

namespace engine
{
	class Engine
	{
	public:

		void loadConfiguration();

		void run();
		float getDeltaTime() const;

		void exit();

		static Engine &getInstance();

		gameplay::GameplayManager &getGameplayM() { return gameplayM; }
		graphics::GraphicsManager &getGraphicsM() { return graphicsM; }
		physics::PhysicsManager &getPhysicsM() { return physicsM; }
		input::InputManager &getInputM() { return inputM; }

	private:

		gameplay::GameplayManager gameplayM;
		graphics::GraphicsManager graphicsM;
		physics::PhysicsManager physicsM;
		input::InputManager inputM;
		
		bool running;
		float deltaTime;

		// Configuration
		std::string startMap;

		static Engine *instance;
	};
}
