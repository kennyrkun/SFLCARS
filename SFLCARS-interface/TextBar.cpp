#include "TextBar.hpp"

#include <iostream>

namespace sflcars
{

TextBar::TextBar(const std::string& string, const TextAlignment align) : align(align)
{
	font.loadFromFile("./resources/fonts/Okuda.otf");
	text.setFont(font);
	text.setCharacterSize(36);
	text.setString(string);
	
	std::cout << "created textbar" << std::endl;
}

void TextBar::setAlignment(TextAlignment align)
{
	this->align = align;
	reposition();
}

void TextBar::setSize(const sf::Vector2f& newSize)
{
	std::cout << "updating bar size" << std::endl;

	// TODO: get 40 from somewhere else
	usableSize.x = newSize.x - (Theme::PADDING * 2);

	leftEdge.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	leftEdge.setCornerPointCount(16);
	leftEdge.setCornersRadius(16);

	leftEdgeRight.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	middle.setSize(sf::Vector2f(usableSize.x - ((barEdgeWidth * 2) + (Theme::MARGIN * 3) + text.getLocalBounds().width), barHeight));

	rightEdge.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	rightEdge.setCornerPointCount(16);
	rightEdge.setCornersRadius(16);

	rightEdgeLeft.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	reposition();
}

sf::Vector2f TextBar::getSize() const
{
	return sf::Vector2f(leftEdge.getSize().x + middle.getSize().x + rightEdge.getSize().x + (Theme::MARGIN * 2), barHeight);
}

void TextBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftEdge);
	target.draw(leftEdgeRight);
	target.draw(middle);
	target.draw(rightEdge);
	target.draw(rightEdgeLeft);
	target.draw(text);
}

void TextBar::reposition()
{
	leftEdge.setPosition(position.x, position.y);
	leftEdgeRight.setPosition(leftEdge.getPosition().x + (barEdgeWidth / 2), position.y);

	if (align == TextAlignment::Left)
	{
		text.setPosition(leftEdge.getPosition().x + leftEdge.getSize().x + Theme::MARGIN, position.y - 7);
		middle.setPosition(text.getPosition().x + text.getGlobalBounds().width + Theme::MARGIN, position.y);
		rightEdge.setPosition(middle.getPosition().x + middle.getSize().x + Theme::MARGIN, position.y);
	}
	else if (align == TextAlignment::Right)
	{
		middle.setPosition(leftEdge.getPosition().x + leftEdge.getSize().x + Theme::MARGIN, position.y);
		text.setPosition(middle.getPosition().x + middle.getSize().x + Theme::MARGIN, position.y - 7);
		rightEdge.setPosition(text.getPosition().x + text.getGlobalBounds().width + Theme::MARGIN, position.y);
	}

	rightEdgeLeft.setPosition(rightEdge.getPosition().x, position.y);
}

}
