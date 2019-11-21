#include "HorizontalLayout.hpp"
#include "Element.hpp"
#include "Display.hpp"

#include <iostream>

namespace sflcars
{

HorizontalLayout::HorizontalLayout(Display* display) : Layout(display)
{
}

Element* HorizontalLayout::add(Element* element, int id)
{
	std::cout << "[Layout] adding element with id " << id << std::endl;

	element->setParent(this);
	element->setID(id);

	sf::Vector2u size = display->getSize();

	if (elements.empty())
		element->setPosition(sf::Vector2f(Theme::MARGIN, Theme::MARGIN));
	else
		element->setPosition(sf::Vector2f(elements.back()->getPosition().x + elements.back()->getSize().x + Theme::MARGIN, elements.back()->getPosition().y));

	elements.push_back(element);
	return element;
}

}
