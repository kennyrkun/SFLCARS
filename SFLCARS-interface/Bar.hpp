#ifndef SFLCARS_BAR_HPP
#define SFLCARS_BAR_HPP

#include "Element.hpp"
#include "RoundRectangle.hpp"

namespace sflcars
{

class Bar : public Element
{
public:
	Bar();

	// TODO: make this just setLength(float length);
	virtual void setSize(const sf::Vector2f& newSize);
	virtual sf::Vector2f getSize() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const { return position; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::RoundedRectangleShape leftEdge;
	sf::RectangleShape leftEdgeRight;

	sf::RectangleShape middle;

	sf::RoundedRectangleShape rightEdge;
	sf::RectangleShape rightEdgeLeft;

	// TODO: define these somewhere else
	const float barHeight = 35;
	const float barEdgeWidth = 50;

	sf::Vector2f usableSize;

	sf::Vector2f position;

	void onWindowResized(sf::Event::SizeEvent newSize);

private:
	virtual void reposition();
};

}

#endif // !SFLCARS_BAR_HPP
