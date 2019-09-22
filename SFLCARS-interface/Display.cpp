#include "Display.hpp"

#include "Layout.hpp"

#include <iostream>

namespace sflcars
{

Display::Display(const sf::VideoMode& size, const int id) : id(id)
{
	sf::ContextSettings context;
	context.antialiasingLevel = 1;

	window = new sf::RenderWindow(size, "SFLCARS", sf::Style::Default, context);
	layout = new Layout(this);

	std::cout << "created Display" << id << std::endl;
}

Display::~Display()
{
	delete window;
	delete layout;

	std::cout << "destroyed Display" << id << std::endl;
}

void Display::setLayout(Layout* layout)
{
	this->layout = layout;
}

Layout* Display::getLayout() const
{
	return layout;
}

sf::Vector2u Display::getWindowSize() const
{
	return window->getSize();
}

sf::Vector2f Display::getMousePosition() const
{
	return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Display::setPadding(float padding)
{
	Theme::PADDING = padding;
}

float Display::getPadding() const
{
	return Theme::PADDING;
}

bool Display::isOpen() const
{
	return window->isOpen();
}

DisplayEvent Display::HandleEvents()
{
	DisplayEvent displayEvent;
	displayEvent.displayID = id;

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

		displayEvent.elementCallbackID = layout->onEvent(event);

		displayEvent.event = event;
		return displayEvent;
    }
}

void Display::Update()
{
}

void Display::Draw()
{
    window->clear();

	window->draw(*layout);

    window->display();
}

}
