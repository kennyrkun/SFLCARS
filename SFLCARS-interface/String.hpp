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

	void setSize(const sf::Vector2f& newSize) {};
	sf::Vector2f getSize() const;

	void setCharacterSize(float newSize);
	float getCharacterSize() const;

	void setFont();
	sf::Font getFont() const;

	void setFillColor(const sf::Color& color);
	const sf::Color& getColor() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Font font;
	sf::Text text;
};

}

#endif // !SFLCARS_STRING_HPP
