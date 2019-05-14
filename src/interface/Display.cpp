#include "Display.hpp"

#include <iostream>

Display::Display(const sf::VideoMode& size, const sf::Vector2i& position, const int id) : id(id)
{
	window = new sf::RenderWindow(size, "SFLCARS");
    window->setPosition(position);

	std::cout << "created Display with id " << id << std::endl;
}

Display::~Display()
{
	std::cout << "destroyed Display with id " << id << std::endl;
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
        else if (event.type == sf::Event::EventType::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
        }

        for (size_t i = 0; i < elements.size(); i++)
            elements[i]->HandleEvents(event);
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