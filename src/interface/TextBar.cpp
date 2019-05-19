#include "TextBar.hpp"

#ifdef _WIN32
	#include <SFML/OpenGL.hpp>
#endif // _WIN32

#include <iostream>

TextBar::TextBar(std::string text, Alignment align) : align(align)
{
	font.loadFromFile("./interface/resources/fonts/Okuda.otf");
	this->text.setFont(font);
	this->text.setCharacterSize(36);
	this->text.setString(text);

	std::cout << "created textbar" << std::endl;
}

void TextBar::setAlignment(Alignment align)
{
	this->align = align;
	reposition();
}

void TextBar::setSize(const sf::Vector2f& newSize)
{
	std::cout << "updating bar size" << std::endl;

	usableSize.x = newSize.x - (edgePadding * 2);

	leftEdge.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	leftEdge.setCornerPointCount(16);
	leftEdge.setCornersRadius(16);

	leftEdgeRight.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	middle.setSize(sf::Vector2f(usableSize.x - ((barEdgeWidth * 2) + (padding * 3) + text.getLocalBounds().width), barHeight));

	rightEdge.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	rightEdge.setCornerPointCount(16);
	rightEdge.setCornersRadius(16);

	rightEdgeLeft.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	reposition();
}

sf::Vector2f TextBar::getSize()
{
	return sf::Vector2f(leftEdge.getSize().x + middle.getSize().x + rightEdge.getSize().x + (padding * 2), barHeight);
}

void TextBar::reposition()
{
	leftEdge.setPosition(position.x + edgePadding, position.y + edgePadding);
	leftEdgeRight.setPosition(leftEdge.getPosition().x + (barEdgeWidth / 2), position.y + edgePadding);

	if (align == Alignment::Left)
	{
		text.setPosition(leftEdge.getPosition().x + leftEdge.getSize().x + padding, position.y + edgePadding - 7);
		middle.setPosition(text.getPosition().x + text.getGlobalBounds().width + padding, position.y + edgePadding);
		rightEdge.setPosition(middle.getPosition().x + middle.getSize().x + padding, position.y + edgePadding);
	}
	else if (align == Alignment::Right)
	{
		middle.setPosition(leftEdge.getPosition().x + leftEdge.getSize().x + padding, position.y + edgePadding);
		text.setPosition(middle.getPosition().x + middle.getSize().x + padding, position.y + edgePadding - 7);
		rightEdge.setPosition(text.getPosition().x + text.getGlobalBounds().width + padding, position.y + edgePadding);
	}

	rightEdgeLeft.setPosition(rightEdge.getPosition().x, position.y + edgePadding);
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
