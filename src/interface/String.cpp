#include "String.hpp"

String::String(const sf::FloatRect& shapeAndSize)
{
	shape = shapeAndSize;
}

void String::setPosition(const sf::Vector2f& newPosition)
{
	shape.left = newPosition.x;
	shape.top = newPosition.y;
}

sf::Vector2f String::getPosition() const
{
	return sf::Vector2f(shape.left, shape.top);
}

void String::setSize(const sf::Vector2f& newSize)
{
	shape.width = newSize.x;
	shape.height = newSize.y;
}

sf::Vector2f String::getSize() const
{
	return sf::Vector2f(shape.width, shape.height);
	// TODO: insert return statement here
}

