#ifndef SFLCARS_SPACER_HPP
#define SFLCARS_SPACER_HPP

#include "Element.hpp"

namespace sflcars
{

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

}

#endif // !SFLCARS_SPACER_HPP
