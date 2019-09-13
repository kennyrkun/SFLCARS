#include "Bar.hpp"

#include <iostream>

Bar::Bar()
{
	std::cout << "created bar" << std::endl;
}

Bar::Bar(const sf::Vector2f& pos)
{
	setPosition(pos);

	std::cout << "created bar at position " << std::endl;
}

void Bar::HandleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::EventType::Resized)
		setSize(sf::Vector2f(event.size.width, event.size.height));
}

void Bar::setSize(const sf::Vector2f& newSize)
{
	std::cout << "updating bar size" << std::endl;

	// TODO: replace 40 with a global edge size somehow
	usableSize.x = newSize.x - (40);

	leftEdge.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	leftEdge.setCornerPointCount(16);
	leftEdge.setCornersRadius(16);

	leftEdgeRight.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	middle.setSize(sf::Vector2f(usableSize.x - ((barEdgeWidth * 2) + (padding * 2)), barHeight));

	rightEdge.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	rightEdge.setCornerPointCount(16);
	rightEdge.setCornersRadius(16);

	rightEdgeLeft.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	reposition();
}

const sf::Vector2f& Bar::getSize() const
{
	return sf::Vector2f(leftEdge.getSize().x + middle.getSize().x + rightEdge.getSize().x + (padding * 2), barHeight);
}

void Bar::setPosition(const sf::Vector2f& newPosition)
{
	std::cout << "updating bar position" << std::endl;

	position = newPosition;

	reposition();
}

void Bar::reposition()
{
	leftEdge.setPosition(position.x, position.y);
	leftEdgeRight.setPosition(leftEdge.getPosition().x + (barEdgeWidth / 2), position.y);
	middle.setPosition(leftEdge.getPosition().x + leftEdge.getSize().x + padding, position.y);
	rightEdge.setPosition(middle.getPosition().x + middle.getSize().x + padding, position.y);
	rightEdgeLeft.setPosition(rightEdge.getPosition().x, position.y);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftEdge, states);
	target.draw(leftEdgeRight, states);
	target.draw(middle, states);
	target.draw(rightEdge, states);
	target.draw(rightEdgeLeft, states);
}
