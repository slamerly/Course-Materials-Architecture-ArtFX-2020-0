#pragma once
#include <memory>
#include <set>
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/graphics/ViewId.h>
#include <engine/graphics/ShapeListObserver.h>

namespace engine
{
	class EventListener;

	namespace graphics
	{
		class View;
		struct ShapeListObserver;

		class GraphicsManager
		{
		public:

			GraphicsManager(EventListener &eventListener_);
			~GraphicsManager();

			bool setUp();
			void clear();

			void pollEvent();
			void draw();

			// Views

			ViewId createView();
			void destroyView(ViewId id);

			void setViewActive(ViewId id);
			void setViewPosition(ViewId id, const sf::Vector2f &position);

			ShapeListId createShapeListInstance(const std::string &name);
			void destroyShapeListInstance(ShapeListId id);

			void setShapeListInstanceMatrix(ShapeListId id, const sf::Transform& matrix);

		private:

			using ViewPtr = std::unique_ptr<View>;
			using ShapeListInstancePtr = std::unique_ptr<ShapeListInstance>;

			EventListener& listener;
			sf::RenderWindow window;
			
			std::set<ViewPtr> Views;
			View *activeView{};

			std::set<ShapeListInstancePtr> _shapeListInstances;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

		};
	}
}
