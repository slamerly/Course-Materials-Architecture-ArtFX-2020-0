#include "engine/graphics/GraphicsManager.hpp"
#include <cassert>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/View.h>
#include <engine/graphics/ShapeListObserver.h>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>


namespace engine
{
	namespace graphics
	{
		GraphicsManager::GraphicsManager(EventListener& eventListener_) : listener{ eventListener_ }
		{

		}

		GraphicsManager::~GraphicsManager()
		{

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

		void GraphicsManager::draw()
		{
			window.clear(sf::Color::Black);

			assert(activeView);
			sf::View view{ activeView->getPosition(), sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT } };
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

		// VIEW

		ViewId GraphicsManager::createView()
		{
			auto view{ new View() };
			Views.insert(ViewPtr{ view });
			return view;
		}

		void GraphicsManager::destroyView(ViewId id)
		{
			auto it = std::find_if(
				std::begin(Views),
				std::end(Views),
				[id](const ViewPtr &view)
				{
					return view.get() == id;
				});
			assert(it != std::end(Views));
			Views.erase(it);
		}

		void GraphicsManager::setViewActive(ViewId id)
		{
			assert(id);
			activeView = id;
		}

		void GraphicsManager::setViewPosition(ViewId id, const sf::Vector2f &position)
		{
			assert(id);
			auto View = id;
			View->setPosition(position);
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

		void GraphicsManager::setShapeListInstanceMatrix(ShapeListId id, const sf::Transform& matrix)
		{
			ShapeListInstance* instance = id;
			instance->transform = matrix;
		}
	}
}