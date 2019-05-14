#include "Bar.hpp"

#include <iostream>

Bar::Bar()
{
	s1.setFillColor(sf::Color::Red);
	ss1.setFillColor(sf::Color::Red);

	s2.setFillColor(sf::Color::Blue);

	std::cout << "created bar" << std::endl;
}

void Bar::HandleEvents(const sf::Event& event)
{
	if (event.type == sf::Event::EventType::Resized)
		updateSizeAndPosition({ event.size.width, event.size.height });
}

void Bar::updateSizeAndPosition(const sf::Vector2u& newSize)
{
	usableSize.x = newSize.x - (edgePadding * 2);
	usableSize.y = newSize.y - (edgePadding * 2);

	s1.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	s1.setCornerPointCount(16);
	s1.setCornersRadius(16);

	ss1.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	s2.setSize(sf::Vector2f(width - ((barEdgeWidth * 2) + (padding * 3) + t.getGlobalBounds().width), barHeight));

	s3.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	s3.setCornerPointCount(16);
	s3.setCornersRadius(16);

	ss3.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	s1.setPosition(edgePadding, edgePadding);
	ss1.setPosition(edgePadding + (barEdgeWidth / 2), edgePadding);
	t.setPosition(s1.getPosition().x + s1.getSize().x + padding, edgePadding - 7);
	s2.setPosition(t.getPosition().x + t.getGlobalBounds().width + padding, edgePadding);
	s3.setPosition(s2.getPosition().x + s2.getSize().x + padding, edgePadding);
	ss3.setPosition(s3.getPosition().x, edgePadding);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(s1);
	target.draw(ss1);
	target.draw(s2);
	target.draw(s3);
	target.draw(ss3);
	target.draw(t);
}
