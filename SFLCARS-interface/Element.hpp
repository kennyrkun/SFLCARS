#ifndef SFLCARS_ELEMENT_HPP
#define SFLCARS_ELEMENT_HPP

#include "Theme.hpp"

#include <SFML/Graphics.hpp>

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
class Layout;

class Element : public sf::Drawable
{
public:
	void setID(int id);
	int getID() const;

	virtual void setSize(const sf::Vector2f& newSize) {}
	virtual sf::Vector2f getSize() const { return sf::Vector2f(0, 0); }

	virtual void setPosition(const sf::Vector2f& newPosition) {};
	virtual sf::Vector2f getPosition() const { return sf::Vector2f(0, 0); };

	virtual void setFillColor(const sf::Color& color) {};
	virtual const sf::Color& getFillColor() const { return sf::Color::White; };

	virtual void setState(State newState);
	State getState() const { return state; };

	// TODO: get this outta here!
	virtual void setDisplay(Display* display);
	virtual Display* getDisplay() const;

	bool isFocused() const;

	bool containsPoint(const sf::Vector2f& point) const;

protected:
	friend class Display;
	friend class Layout;
	friend class HorizontalLayout;
	friend class VerticalLayout;

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

	Layout* parent = nullptr;

	void setParent(Layout* element);
	Layout* getParent() const;

	// Return the layout, if this element is one.
	virtual Layout* toLayout() { return nullptr; }

private:
	State state;
	int id = -1;
};

}

#endif // !SFLCARS_ELEMENT_HPP
