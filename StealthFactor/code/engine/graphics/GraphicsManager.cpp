#include "engine/graphics/GraphicsManager.hpp"
#include <SFML/Window/Event.hpp>
#include <engine/graphics/ViewProvider.h>

namespace engine
{
	namespace graphics
	{
		GraphicsManager::GraphicsManager(ViewProvider& viewprovider_, EventListener& eventListener_) :
			center{ viewprovider_ },
			listener{ eventListener_ }
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

		void GraphicsManager::draw()
		{
			window.clear(sf::Color::Black);

			sf::View view{ center.getViewCenter(),sf::Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT) };
			window.setView(view);


			for (auto &instance : _shapeListInstances)
			{
				sf::RenderStates renderStates{ instance->transform };

				for (auto& shape : instance->shapeList.getShapes())
				{
					window.draw(*shape, renderStates);
				}
			}

			window.display();
		}

		bool GraphicsManager::setUp()
		{
			window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");

			if (!window.isOpen())
			{
				return false;
			}

			window.setVerticalSyncEnabled(true);

			return true;
		}

		void GraphicsManager::clear()
		{
			assert(_shapeListInstances.size() == 0);

			window.close();
		}

		void GraphicsManager::pollEvent()
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				listener.onEvent(event);
			}
		}

		ShapeListId GraphicsManager::createShapeListInstance(const std::string& name)
		{
			auto instance{ new ShapeListInstance() };
			ShapeListInstancePtr instanceUPtr{ instance };

			if (!instance->shapeList.load(name))
			{
				return nullptr;
			}

			_shapeListInstances.insert(std::move(instanceUPtr));
			return instance;
		}

		void GraphicsManager::destroyShapeListInstance(ShapeListId id)
		{
			auto it = std::find_if(std::begin(_shapeListInstances), std::end(_shapeListInstances), [id](const ShapeListInstancePtr& instance)
				{
					return instance.get() == id;
				});
			assert(it != std::end(_shapeListInstances));
			_shapeListInstances.erase(it);
		}

		void GraphicsManager::setShapeListInstanceTransform(ShapeListId id, const sf::Transform& transform)
		{
			ShapeListInstance* instance = id;
			instance->transform = transform;
		}

		void GraphicsManager::setShapeListInstanceMatrix(ShapeListId id, const sf::Transform& matrix)
		{
			ShapeListInstance* instance = id;
			instance->transform = matrix;
		}
	}
}