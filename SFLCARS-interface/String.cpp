#include "String.hpp"

namespace sflcars
{

String::String(const std::string& string)
{
	text.setFont(Theme::getFont());
	text.setCharacterSize(Theme::textCharacterSize);
	text.setString(string);
}

void String::setPosition(const sf::Vector2f& newPosition)
{
	text.setPosition(sf::Vector2f(newPosition.x, newPosition.y - 11));
}

sf::Vector2f String::getPosition() const
{
	sf::Vector2f position = text.getPosition();
	position.y += 11;
	return position;
}

sf::Vector2f String::getSize() const
{
	sf::FloatRect rect = text.getGlobalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void String::setText(const sf::String& string)
{
	text.setString(string);
}

const sf::String& String::getText() const
{
	return text.getString();
}

void String::addText(const sf::String& string)
{
	setText(getText() + string);
}

bool String::isEmpty() const
{
	return text.getString().isEmpty();
}

void String::setCharacterSize(float newSize)
{
	text.setCharacterSize(newSize);
}

int String::getCharacterSize() const
{
	return text.getCharacterSize();
}

void String::setFont(sf::Font& font)
{
	text.setFont(font);
}

sf::Font String::getFont() const
{
	return *text.getFont();
}

void String::setFillColor(const sf::Color& color)
{
	text.setFillColor(color);
}

const sf::Color& String::getColor() const
{
	return text.getFillColor();
}

void String::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}

}
