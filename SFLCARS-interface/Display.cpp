#include "Display.hpp"

#include "Layout.hpp"

#include <iostream>

namespace sflcars
{

Display::Display(const sf::VideoMode& size, int id) : RenderWindow(size, "SFLCARS", sf::Style::Default), id(id)
{
	layout = new Layout(this);

	std::cout << "created Display" << id << std::endl;
}

Display::~Display()
{
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

sf::Vector2f Display::getMousePosition() const
{
	return mapPixelToCoords(sf::Mouse::getPosition(*this));
}

void Display::setPadding(float padding)
{
	Theme::PADDING = padding;
}

float Display::getPadding() const
{
	return Theme::PADDING;
}

DisplayEvent Display::HandleEvents()
{
	DisplayEvent displayEvent;
	displayEvent.displayID = id;

    sf::Event event;
    if (isOpen())
    {
        pollEvent(event);

        if (event.type == sf::Event::EventType::Closed)
            close();
        else if (event.type == sf::Event::EventType::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            setView(sf::View(visibleArea));
		}

		displayEvent.elementCallbackID = layout->onEvent(event);

		displayEvent.event = event;
		return displayEvent;
    }
}

void Display::Update()
{
}

void Display::DrawLayout()
{
	draw(*layout);
}

}
