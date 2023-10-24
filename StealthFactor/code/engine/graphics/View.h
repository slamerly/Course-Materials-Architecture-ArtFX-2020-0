#pragma once

#include <SFML/Graphics/Transform.hpp>

namespace engine
{
	namespace graphics
	{
		class View
		{
		public:

			const sf::Vector2f& getPosition() const;
			void setPosition(const sf::Vector2f &position);

		private:

			sf::Vector2f _position;
		};
	}
}
