#ifndef BAR_HPP
#define BAR_HPP

#include "Element.hpp"

class Bar : public Element
{
public:
	Bar();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape;
};

#endif // !BAR_HPP