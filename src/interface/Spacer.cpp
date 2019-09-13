#include "Spacer.hpp"

Spacer::Spacer(const sf::FloatRect& shapeAndSize)
{
	shape = shapeAndSize;
}

void Spacer::setPosition(const sf::Vector2f& newPosition)
{
	shape.left = newPosition.x;
	shape.top = newPosition.y;
}

sf::Vector2f Spacer::getPosition() const
{
	return sf::Vector2f(shape.left, shape.top);
}

void Spacer::setSize(const sf::Vector2f& newSize)
{
	shape.width = newSize.x;
	shape.height = newSize.y;
}

sf::Vector2f Spacer::getSize() const
{
	return sf::Vector2f(shape.width, shape.height);
	// TODO: insert return statement here
}

