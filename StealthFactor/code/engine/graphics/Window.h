#pragma once

#include <SFML/Graphics/RenderWindow.hpp>


namespace engine
{
	namespace graphics
	{
		class Window
		{
		public:
			static const sf::Int16 getWINDOW_WIDTH() { return WINDOW_WIDTH; }
			static const sf::Int16 getWINDOW_HEIGHT() { return WINDOW_HEIGHT; }

		private:
			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

		};
	}
}

