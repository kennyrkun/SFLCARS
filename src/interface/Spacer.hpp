#ifndef SPACER_HPP
#define SPACER_HPP

#include "Element.hpp"

class Spacer : public Element
{
public:
	Spacer(const sf::FloatRect& shapeAndSize);

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	void setSize(const sf::Vector2f& newSize);
	sf::Vector2f getSize() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {};

private:
	sf::FloatRect shape;
};

#endif // !SPACER_HPP
