#include "Window.h"

namespace engine
{
    namespace graphics
    {
        Window::Window()
        {
        }

        Window::~Window()
        {
            window.close();
        }

        bool Window::createWindow(int width, int height, const std::string& title)
        {
            if (window.isOpen())
            {
                window.close();
            }

            window.create(sf::VideoMode(width, height), title);
            window.setVerticalSyncEnabled(true);
            view.setSize(static_cast<float>(width), static_cast<float>(height));

            return window.isOpen();
        }

        void Window::clear(sf::Color clearColor)
        {
            window.clear(clearColor);
        }

        void Window::display()
        {
            window.display();
        }

        void Window::pollEvent(sf::Event& event)
        {
            while (window.pollEvent(event))
            {
                // Handle events here
            }
        }

        void Window::setViewCenter(const sf::Vector2f& center)
        {
            view.setCenter(center);
            window.setView(view);
        }

        sf::RenderWindow& Window::getRenderWindow()
        {
            return window;
        }
    }
}
