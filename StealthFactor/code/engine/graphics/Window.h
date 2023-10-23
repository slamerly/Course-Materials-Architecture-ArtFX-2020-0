#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace engine
{
    namespace graphics
    {
        class Window
        {
        public:
            Window();
            ~Window();

            bool createWindow(int width, int height, const std::string& title);
            void clear(sf::Color clearColor = sf::Color::Black);
            void display();
            void pollEvent(sf::Event& event);
            void setViewCenter(const sf::Vector2f& center);
            sf::RenderWindow& getRenderWindow();

        private:
            sf::RenderWindow window;
            sf::View view;
        };
    }
}
