#include "Display.hpp"

Display(const sf::VideoMode& size, const sf::Vector2f& position);
{
    window = sf::RenderWindow(size, "SFLCARS");
    window.setPosition(position);
}

void HandleEvents()
{
    sf::Event event;
    if (window.isOpen())
    {
        window.pollEvent(event);

        if (event.type == sf::Event::EventType::Closed)
            window.close();
    }
}

void Update()
{

}

void Draw()
{
    window.clear();
    window.display();
}