#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

#include <vector>

enum class State
{
	Hovered,
	Pressed,
	Focused
};

class Element : public sf::Drawable
{
public:
	// required
	virtual void HandleEvents(const sf::Event& event, sf::RenderWindow& window) = 0;

	// optional
	virtual void setSize(const sf::Vector2f& newSize) { return; }
	// optional
	virtual sf::Vector2f getSize() const { return sf::Vector2f(); };

	// required
	virtual void setPosition(const sf::Vector2f& newPosition) = 0;
	// required
	virtual sf::Vector2f getPosition() const = 0;

	//virtual void setColor(const sf::Color& color) = 0;
	//virtual sf::Color& const getColor() = 0;

	virtual void setState(State newState) { state = newState; };
	State getState() const { return state; };

	int id;

private:
	State state;
};

#endif // !ELEMENT_HPP
