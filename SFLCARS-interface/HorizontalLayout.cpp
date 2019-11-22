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
	std::cout << "[HorizontalLayout] adding element with id " << id << std::endl;

	element->setParent(this);
	element->setID(id);

	if (elements.empty())
		element->setPosition(sf::Vector2f(position.x + Theme::MARGIN, position.y + Theme::MARGIN));
	else
		element->setPosition(sf::Vector2f(position.x + elements.back()->getPosition().x + elements.back()->getSize().x + Theme::MARGIN, position.y + elements.back()->getPosition().y));

	return push(element);
}

void HorizontalLayout::recomputeGeometry()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f size;

	for (Element* element : elements)
	{
		element->setPosition(pos);
		pos.x += element->getSize().x + Theme::MARGIN;

		// Layout's height is the tallest widget's height
		if (element->getSize().y > size.y)
			size.y = element->getSize().y;
	}

	size.x = pos.x - Theme::MARGIN;
	setSize(size);
}

}
