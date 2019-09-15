#include "Element.hpp"
#include "Display.hpp"

#include <random>

void Element::setID(int id)
{
	this->id = id;
}

int Element::getID() const
{
	return id;
}

sf::Color Element::getRandomColor(int lower, int upper, bool single)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

	if (single)
	{
		int i = dist(rng);
		return sf::Color(i, i, i);
	}
	else
		return sf::Color(dist(rng), dist(rng), dist(rng));
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

// callbacks

void Element::onStateChanged(State) {}
//void Element::onWindowResized(const sf::Vector2f&) {}
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
