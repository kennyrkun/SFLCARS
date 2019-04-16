#include "Display.hpp"

#include <iostream>

Display::Display(const sf::VideoMode& size, const sf::Vector2i& position, const int id) : id(id)
{
	window = new sf::RenderWindow(size, "SFLCARS");
    window->setPosition(position);

	std::cout << "created Display" << std::endl;
}

Display::~Display()
{
	std::cout << "destroyed Display" << std::endl;
}

void Display::addElement(Element* element)
{
	elements.push_back(element);
}

void Display::HandleEvents()
{
    sf::Event event;
    if (window->isOpen())
    {
        window->pollEvent(event);

        if (event.type == sf::Event::EventType::Closed)
            window->close();
    }
}

void Display::Update()
{

}

void Display::Draw()
{
    window->clear();

	for (size_t i = 0; i < elements.size(); i++)
		window->draw(*elements[i]);

    window->display();
}