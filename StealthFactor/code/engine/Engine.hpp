#pragma once

#include <string>

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>

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

		gameplay::Manager &getGameplayM() { return gameplayM; }
		graphics::Manager &getGraphicsM() { return graphicsM; }
		physics::Manager &getPhysicsM() { return physicsM; }
		input::Manager &getInputM() { return inputM; }

	private:
		gameplay::Manager gameplayM;
		graphics::Manager graphicsM;
		physics::Manager physicsM;
		input::Manager inputM;
		

		bool running;
		float deltaTime;

		// Configuration
		std::string startMap;

		static Engine *instance;
	};
}
