#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/graphics/ShapeList.hpp>

namespace engine
{
	namespace graphics
	{
		class ShapeList;

		class Manager
		{
		public:
			Manager();
			~Manager();

			void clear();
			void draw(const ShapeList &shapeList, const sf::Transform &transform);
			void display();

			bool hasFocus() const;

			static Manager &getInstance();

			static sf::RenderWindow &getWindow() { return window; }

			static const sf::Int16 getWINDOW_WIDTH() { return WINDOW_WIDTH; }
			static const sf::Int16 getWINDOW_HEIGHT() { return WINDOW_HEIGHT; }

		private:
			static sf::RenderWindow window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

			static Manager *instance;
		};
	}
}
