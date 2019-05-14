#ifndef BAR_HPP
#define BAR_HPP

#include "Element.hpp"
#include "../utility/RoundRectangle.hpp"

class Bar : public Element
{
public:
	Bar();

	void HandleEvents(const sf::Event& event);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void updateSizeAndPosition(const sf::Vector2u& newSize);const float edgePadding = 20.0f;

	const float padding = 10.0f;

	sf::Vector2f usableSize;

	float width = 0.0f;
	float height = 0.0f;

	const float barEdgeWidth = 50;
	const float barHeight = 35;

	sf::RoundedRectangleShape s1;
	sf::RectangleShape ss1;

	sf::RectangleShape s2;

	sf::RoundedRectangleShape s3;
	sf::RectangleShape ss3;

	sf::Text t;
};

#endif // !BAR_HPP