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
	std::cout << "adding new element" << std::endl;
	std::cout << elements.size() << std::endl;

	int padding = 20;

	element->setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	element->setPosition(sf::Vector2f(padding, padding)); // HACK: get it to calculate it's geometry before we start moving things

	if (!elements.empty())
	{
		if (elements.size() < 2) // make it the bottom piece
			element->setPosition(sf::Vector2f(padding, padding));
		else
		{
			std::cout << "repositioning last element" << std::endl;

			// set the position of the last element to behind the previous element
			Element* back = elements[elements.size() - 2]; // because -1 is .back()
			elements.back()->setPosition(sf::Vector2f(padding, back->getPosition().y + back->getSize().y + padding));

			// TODO: don't put buttons at the back

			// put the new element at the bottom of the display
			element->setPosition(sf::Vector2f(padding, window->getSize().y - 75));
		}
	}

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
            elements[i]->HandleEvents(event, *window);
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
