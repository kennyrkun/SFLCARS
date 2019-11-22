#include "VerticalLayout.hpp"
#include "Element.hpp"
#include "Display.hpp"

#include <iostream>

namespace sflcars
{

VerticalLayout::VerticalLayout(Display* display) : Layout(display)
{
	size = sf::Vector2f(0, 0);
}

Element* VerticalLayout::add(Element* element, int id)
{
	std::cout << "[VerticalLayout] adding element with id " << id << std::endl;

	element->setParent(this);
	element->setID(id);

	if (elements.empty())
		element->setPosition(sf::Vector2f(position.x + Theme::MARGIN, position.y + Theme::MARGIN));
	else
		element->setPosition(sf::Vector2f(position.x + Theme::MARGIN, position.y + elements.back()->getPosition().y + elements.back()->getSize().y + Theme::MARGIN));

	return push(element);
}

void VerticalLayout::recomputeGeometry()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	for (Element* element : elements)
	{
		element->setPosition(pos);
		pos.y += element->getSize().y + Theme::MARGIN;

		// Layout's width is the wider widget's width
		if (element->getSize().x > size.x)
			size.x = element->getSize().x;
	}

	size.y = pos.y - Theme::MARGIN;
	setSize(size);
}

}
