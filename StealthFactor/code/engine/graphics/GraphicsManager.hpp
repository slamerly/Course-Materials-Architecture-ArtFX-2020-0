#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/Engine.hpp>

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

			void update();

			void clear();
			void draw(const ShapeList &shapeList, const sf::Transform &transform);
			void display();

			bool hasFocus() const;

			static Manager &getInstance();

		private:
			sf::RenderWindow window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

			static Manager *instance;
		};
	}
}
