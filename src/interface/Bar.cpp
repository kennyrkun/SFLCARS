#include "Bar.hpp"

#include <iostream>

Bar::Bar()
{
	shape.setSize(sf::Vector2f(100, 100));

	std::cout << "created bar" << std::endl;
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);

	std::cout << "drwaing" << std::endl;
}
