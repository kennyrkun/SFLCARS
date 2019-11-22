#include "Layout.hpp"
#include "VerticalLayout.hpp"
#include "HorizontalLayout.hpp"
#include "Display.hpp"
#include "Element.hpp"

#include <iostream>

namespace sflcars
{

Layout::Layout(Display* display) : display(display)
{
}

Layout::~Layout()
{
}

void Layout::setDisplay(Display* display)
{
	// TODO: allow this
	abort();
}

Display* Layout::getDisplay() const
{
	return display;
}

void Layout::setSize(const sf::Vector2f& newSize)
{
	// TODO: this might not be legal
	size = newSize;
}

sf::Vector2f Layout::getSize() const
{
	return size;
}

void Layout::setPosition(const sf::Vector2f& newPosition)
{
	std::cout << "set layout position" << std::endl;

	// TODO: might need to update the position of all the objects that are contained within this object
	position = newPosition;
}

sf::Vector2f Layout::getPosition() const
{
	return position;
}

VerticalLayout* Layout::addVerticalLayout()
{
	VerticalLayout* layout = new VerticalLayout(display);
	add(layout);
	return layout;
}

HorizontalLayout* Layout::addHorizontalLayout()
{
	HorizontalLayout* layout = new HorizontalLayout(display);
	add(layout);
	return layout;
}

Element* Layout::push(Element* element)
{
	elements.push_back(element);
	recomputeGeometry();
	return element;
}

int Layout::onEvent(const sf::Event& event)
{
	sf::Vector2f mouse = display->getMousePosition();

	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		onMouseMoved(mouse);
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			onMousePressed(mouse);
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			onMouseReleased(mouse);
		break;
	}
	case sf::Event::MouseWheelMoved:
		onMouseWheelMoved(event.mouseWheel.delta);
		break;
	case sf::Event::KeyPressed:
		onKeyPressed(event.key.code);
		break;
	case sf::Event::KeyReleased:
		onKeyReleased(event.key.code);
		break;
	case sf::Event::TextEntered:
		onTextEntered(event.text.unicode);
		break;
	case sf::Event::Resized:
		onWindowResized(event.size);
		break;
	default:
		break;
	}

	if (triggered != nullptr)
	{
		int id = triggered->getID();
		triggered = nullptr;
		return id;
	}

	return -1;
}

bool Layout::focusNextElement()
{
	for (size_t i = 0; i < elements.size(); i++)
		if (elements[i] != nullptr)
			if (elements[i] == focused)
				if (focusElement(elements[i + 1], State::Focused))
					return true;

	if (focused != nullptr)
		focused->setState(State::Default);
	focused = nullptr;

	return false;
}

bool Layout::focusPreviousElement()
{
	for (size_t i = 0; i < elements.size(); i++)
		if (elements[i] != nullptr)
			if (elements[i] == focused)
				if (focusElement(elements[i - 1], State::Focused))
					return true;

	if (focused != nullptr)
		focused->setState(State::Default);
	focused = nullptr;

	return false;
}

bool Layout::focusElement(Element* element, State state)
{
	if (element != nullptr)
	{
		// If another element was already focused, remove focus
		if (focused != nullptr &&
			focused != element) // and that element is not this element
		{
			focused->setState(State::Default);
			focused = nullptr;
		}

		focused = element;
		element->setState(state);
		return true;
	}

	return false;
}

void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setSize(getSize());
	shape.setPosition(getPosition());
	shape.setFillColor(Theme::getRandomColor());
	target.draw(shape, states);

	for (const auto element : elements)
		target.draw(*element, states);
}

}
