#ifndef BAR_HPP
#define BAR_HPP

#include "Element.hpp"
#include "../utility/RoundRectangle.hpp"

class Bar : public Element
{
public:
	Bar();
	Bar(const sf::Vector2f& pos);

	void HandleEvents(const sf::Event& event);

	// TODO: make this just setLength(float length);
	virtual void updateSize(const sf::Vector2f& newSize);

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() { return position; }

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
	const float padding = 10.0f;
	const float edgePadding = 20.0f;

	sf::Vector2f usableSize;

	sf::Vector2f position;

private:
	virtual void reposition();
};

#endif // !BAR_HPP