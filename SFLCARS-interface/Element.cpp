#include "Element.hpp"
#include "Display.hpp"
#include "Layout.hpp"

#include <iostream>

namespace sflcars
{

void Element::setID(int id)
{
	this->id = id;
}

int Element::getID() const
{
	return id;
}

void Element::setState(State newState)
{
	state = newState;
	onStateChanged(state);
}

void Element::setDisplay(Display* display)
{
}

Display* Element::getDisplay() const
{
	return nullptr;
}

void Element::setParent(Element* element)
{
	parent = element;
}

Element* Element::getParent() const
{
	return parent;
}

bool Element::isFocused() const
{
	return (state == State::Focused);
}

bool Element::containsPoint(const sf::Vector2f& point) const
{
	sf::Vector2f position = getPosition();
	sf::Vector2f size = getSize();
	sf::FloatRect rect(position.x, position.y, size.x, size.y);

	return rect.contains(point);
}

// callbacks

void Element::onStateChanged(State) {}
void Element::onWindowResized(sf::Event::SizeEvent) {}
void Element::onMouseMoved(const sf::Vector2f&) {}
void Element::onMousePressed(const sf::Vector2f&) {}
void Element::onMouseReleased(const sf::Vector2f&) {}
void Element::onMouseWheelMoved(int) {}
void Element::onKeyPressed(const sf::Keyboard::Key&) {}
void Element::onKeyReleased(const sf::Keyboard::Key&) {}
void Element::onTextEntered(const sf::Uint32&) {}

void Element::triggerCallback()
{
	parent->triggered = this;
}

}
