#include "VerticalLayout.hpp"
#include "Element.hpp"
#include "Display.hpp"

#include <iostream>

namespace sflcars
{

VerticalLayout::VerticalLayout(Display* display) : Layout(display)
{
}

Element* VerticalLayout::add(Element* element, int id)
{
	std::cout << "[VerticalLayout] adding element with id " << id << std::endl;

	element->setParent(this);
	element->setID(id);

	sf::Vector2u size = display->getSize();

	if (elements.empty())
		element->setPosition(sf::Vector2f(Theme::MARGIN, Theme::MARGIN));
	else
		element->setPosition(sf::Vector2f(Theme::MARGIN, elements.back()->getPosition().y + elements.back()->getSize().y + Theme::MARGIN));

	return push(element);
}

}
