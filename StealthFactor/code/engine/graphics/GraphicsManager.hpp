#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/IManager.hpp>

namespace engine
{
	namespace graphics
	{
		class ShapeList;

		class GraphicsManager : public IManager
		{
		public:

			GraphicsManager();
			~GraphicsManager();

			void initialize() override;
			void update() override;
			void clear() override;

			//void clear();
			void draw(const ShapeList &shapeList, const sf::Transform &transform);
			void display();

			static sf::RenderWindow &getWindow() { return window; }

			static const sf::Int16 getWINDOW_WIDTH() { return WINDOW_WIDTH; }
			static const sf::Int16 getWINDOW_HEIGHT() { return WINDOW_HEIGHT; }

			bool hasFocus() const;

		private:

			static sf::RenderWindow window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

		};
	}
}
