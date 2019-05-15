#include "Bar.hpp"

#include <iostream>

Bar::Bar()
{
	middle.setFillColor(sf::Color::Red);

	std::cout << "created bar" << std::endl;
}

Bar::Bar(const sf::Vector2f& pos)
{
	setPosition(pos);

	std::cout << "created bar at position " << std::endl;
}

void Bar::HandleEvents(const sf::Event& event)
{
	if (event.type == sf::Event::EventType::Resized)
		updateSize({ event.size.width, event.size.height });
}

void Bar::updateSize(const sf::Vector2u& newSize)
{
	std::cout << "updating bar size" << std::endl;

	usableSize.x = newSize.x - (edgePadding * 2);
	usableSize.y = newSize.y - (edgePadding * 2);

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

void Bar::setPosition(const sf::Vector2f& newPosition)
{
	std::cout << "updating bar position" << std::endl;

	position = newPosition;

	reposition();
}

void Bar::reposition()
{
	leftEdge.setPosition(edgePadding, edgePadding);
	leftEdgeRight.setPosition(leftEdge.getPosition().x + (barEdgeWidth / 2), edgePadding);
	middle.setPosition(leftEdge.getPosition().x + leftEdge.getSize().x + padding, edgePadding);
	rightEdge.setPosition(middle.getPosition().x + middle.getSize().x + padding, edgePadding);
	rightEdgeLeft.setPosition(rightEdge.getPosition().x, edgePadding);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftEdge);
	target.draw(leftEdgeRight);
	target.draw(middle);
	target.draw(rightEdge);
	target.draw(rightEdgeLeft);
}
