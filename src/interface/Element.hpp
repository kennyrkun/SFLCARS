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
	void setID(int id);
	int getID() const;

	// required
	virtual void HandleEvents(const sf::Event& event, sf::RenderWindow& window) = 0;

	// optional
	virtual void setSize(const sf::Vector2f& newSize) { return; }
	// optional
	virtual sf::Vector2f getSize() const { return sf::Vector2f(0, 0); }

	// required
	virtual void setPosition(const sf::Vector2f& newPosition) = 0;
	// required
	virtual sf::Vector2f getPosition() const = 0;

	//virtual void setColor(const sf::Color& color) = 0;
	//virtual sf::Color& const getColor() = 0;

	// TODO: add upper and lower bounds to this
	// int lower: the lower boundary for colour
	// int upper: the upper boundary for colour
	sf::Color getRandomColor(int lower = 100, int upper = 255);

	virtual void setState(State newState) { state = newState; };
	State getState() const { return state; };

	void setSelectable(bool selectable);

	bool isSelectable() const;

	virtual void onStateChanged(State state);
	virtual void onMouseMoved(const sf::Vector2f& position);
	virtual void onMousePressed(const sf::Vector2f& position);
	virtual void onMouseReleased(const sf::Vector2f& position);
	virtual void onMouseWheelMoved(int delta);
	virtual void onKeyPressed(const sf::Keyboard::Key& key);
	virtual void onKeyReleased(const sf::Keyboard::Key& key);
	virtual void onTextEntered(const sf::Uint32& unicode);

private:
	State state;
	int id;
	bool selectable;
};

#endif // !ELEMENT_HPP
