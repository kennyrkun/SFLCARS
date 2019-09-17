#include "Element.hpp"
#include "Display.hpp"

#include <random>

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

void Element::setParent(Display* display)
{
	this->parent = display;
}

Display* Element::getParent() const
{
	return parent;
}

void Element::setSelectable(bool selectable)
{
	this->selectable = selectable;
}

bool Element::isSelectable() const
{
	return selectable;
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
