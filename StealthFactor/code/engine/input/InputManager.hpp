#pragma once
#include <set>
#include <SFML/Window/Event.hpp>
#include <set>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <engine/IManager.hpp>

namespace engine
{
	namespace input
	{
		class InputManager : public IManager
		{
		public:

			void initialize() override;
			void update() override;
			void clear() override;

			// True during all frames while the key is pressed.
			bool isKeyPressed(sf::Keyboard::Key key) const;

			// True only the first frame after that the key is pressed.
			bool isKeyJustPressed(sf::Keyboard::Key key) const;

			// True only the first frame after that the key is released.
			bool isKeyJustReleased(sf::Keyboard::Key key) const;

			//void clear();
			void onKeyPressed(const sf::Event::KeyEvent &event);
			void onKeyReleased(const sf::Event::KeyEvent &event);

			bool hasFocus() const;

		private:

			std::set<sf::Keyboard::Key> justPressedKeys;
			std::set<sf::Keyboard::Key> justReleasedKeys;
		};
	}
}
