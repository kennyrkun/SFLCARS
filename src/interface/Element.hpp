#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include <vector>

class Element : public sf::Drawable
{
public:
	virtual void HandleEvents(const sf::Event& event) = 0;

	// optional
	virtual void setSize(const sf::Vector2f& newSize) {	return; }
	// optional
	virtual sf::Vector2f getSize() { return sf::Vector2f(); };

	// required
	virtual void setPosition(const sf::Vector2f& newPosition) = 0;
	// required
	virtual sf::Vector2f getPosition() = 0;

	int id;
};

#endif // !ELEMENT_HPP
