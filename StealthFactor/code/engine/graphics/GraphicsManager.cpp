#include "engine/graphics/GraphicsManager.hpp"

namespace engine
{
	namespace graphics
	{
		GraphicsManager::GraphicsManager()
		{
			window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");

			window.setVerticalSyncEnabled(true);

			sf::View view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
			window.setView(view);
		}

		GraphicsManager::~GraphicsManager()
		{
			window.close();
		}

		void GraphicsManager::initialize()
		{
			// Initialisation
		}

		void GraphicsManager::update()
		{
		}

		void GraphicsManager::clear()
		{
			window.clear(sf::Color::Black);

			/*sf::View view{ gameplay::GraphicsManager::getInstance().getViewCenter(), sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT} };
			window.setView(view);*/
		}

		void GraphicsManager::draw(const ShapeList &shapeList, const sf::Transform &transform)
		{
			sf::RenderStates renderStates{ transform };
			for (auto shape : shapeList.getShapes())
			{
				window.draw(*shape, renderStates);
			}
		}

		void GraphicsManager::display()
		{
			window.display();
		}

		bool GraphicsManager::hasFocus() const
		{
			return hasFocus();
		}
	}
}
