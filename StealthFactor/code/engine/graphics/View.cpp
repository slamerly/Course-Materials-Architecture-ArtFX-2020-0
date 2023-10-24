#include "View.h"

namespace engine
{
	namespace graphics
	{
		const sf::Vector2f& View::getPosition() const
		{
			return _position;
		}

		void View::setPosition(const sf::Vector2f& position)
		{
			_position = position;
		}
	}
}
