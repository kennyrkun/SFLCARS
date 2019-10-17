#ifndef SFLCARS_STRING_HPP
#define SFLCARS_STRING_HPP

#include "Element.hpp"

namespace sflcars
{

class String : public Element
{
public:
	String(const std::string& string);

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	void setText(const sf::String& string);
	const sf::String& getText() const;

	void addText(const sf::String& string);

	bool isEmpty() const;

	void setCharacterSize(float newSize);
	int getCharacterSize() const;

	void setFont(sf::Font& font);
	sf::Font getFont() const;

	void setFillColor(const sf::Color& color);
	const sf::Color& getColor() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Text text;
};

}

#endif // !SFLCARS_STRING_HPP
