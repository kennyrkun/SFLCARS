#ifndef SFLCARS_ELEMENT_HPP
#define SFLCARS_ELEMENT_HPP

#include "Theme.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace sflcars
{

enum class State
{
	Default,
	Hovered,
	Pressed,
	Focused
};

class Display;

class Element : public sf::Drawable
{
public:
	void setID(int id);
	int getID() const;

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

	virtual void setState(State newState);
	State getState() const { return state; };

	void setParent(Display* display);
	Display* getParent() const;

	void setSelectable(bool selectable);

	bool isSelectable() const;
	bool isFocused() const;

	bool containsPoint(const sf::Vector2f& point) const;

protected:
	friend class Display;
	friend class Layout;

	virtual void onStateChanged(State state);

	virtual void onWindowResized(sf::Event::SizeEvent size);
	virtual void onMouseMoved(const sf::Vector2f& position);
	virtual void onMousePressed(const sf::Vector2f& position);
	virtual void onMouseReleased(const sf::Vector2f& position);
	virtual void onMouseWheelMoved(int delta);
	virtual void onKeyPressed(const sf::Keyboard::Key& key);
	virtual void onKeyReleased(const sf::Keyboard::Key& key);
	virtual void onTextEntered(const sf::Uint32& unicode);

	void triggerCallback();

private:
	State state;
	int id = -1;
	bool selectable;

	Display* parent;
};

}

#endif // !SFLCARS_ELEMENT_HPP
