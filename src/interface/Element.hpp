#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

class Element : public sf::Drawable
{
public:
	virtual void HandleEvents(const sf::Event& event) = 0;

	virtual void updateSize(const sf::Vector2f& newSize) = 0;
	virtual void setPosition(const sf::Vector2f& newPosition) = 0;
	virtual sf::Vector2f getPosition() = 0;

	int id;
};

#endif // !ELEMENT_HPP
