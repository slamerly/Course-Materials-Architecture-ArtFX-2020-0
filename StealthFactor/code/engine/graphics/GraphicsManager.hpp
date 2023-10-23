#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>
#include <set>
#include <memory>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/graphics/ShapeListObserver.h>
#include <engine/EventListener.h>

namespace engine
{
	class EventListener;

	namespace graphics
	{
		class ShapeList;
		class ViewProvider;

		struct ShapeListObserver;

		class GraphicsManager
		{
		public:

			GraphicsManager(ViewProvider &viewprovider_, EventListener &eventListener_);
			~GraphicsManager();

			//void clear();
			void draw();

			bool setUp();
			void clear();

			void pollEvent();

			ShapeListId createShapeListInstance(const std::string& name);

			void destroyShapeListInstance(ShapeListId id);
			void setShapeListInstanceTransform(ShapeListId id, const sf::Transform& transform);

			void setShapeListInstanceMatrix(ShapeListId id, const sf::Transform& matrix);

		private:

			sf::RenderWindow window;
			using ShapeListInstancePtr = std::unique_ptr<ShapeListInstance>;

			ViewProvider &center;
			EventListener &listener;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

			std::set<ShapeListInstancePtr> _shapeListInstances;

		};
	}
}
