#include "Layout.hpp"
#include "Display.hpp"
#include "Button.hpp"
#include "Bar.hpp"
#include "TextBar.hpp"
#include "Theme.hpp"

namespace sflcars
{

VerticalLayout::VerticalLayout(Display* display) : display(display)
{
}

VerticalLayout::~VerticalLayout()
{
}

void VerticalLayout::setDisplay(Display* display)
{
	// TODO: allow this
	abort();
}

Display* VerticalLayout::getDisplay() const
{
	return display;
}

void VerticalLayout::setSize(const sf::Vector2f& newSize)
{
	// TODO: this might not be legal
	size = newSize;
}

sf::Vector2f VerticalLayout::getSize() const
{
	return size;
}

void VerticalLayout::setPosition(const sf::Vector2f& newPosition)
{
}

sf::Vector2f VerticalLayout::getPosition() const
{
	return sf::Vector2f();
}

Element* VerticalLayout::add(Element* element, Alignment align, int id)
{
	std::cout << "[VerticalLayout] adding element with id " << id << std::endl;

	element->setParent(this);
	element->setID(id);

	sf::Vector2u size = display->getSize();

	if (elements.empty())
		element->setPosition(sf::Vector2f(Theme::MARGIN, Theme::MARGIN));
	else
		if (align == Alignment::Vertical)
			element->setPosition(sf::Vector2f(Theme::MARGIN, elements.back()->getPosition().y + elements.back()->getSize().y + Theme::MARGIN));
		else if (align == Alignment::Horizontal)
			element->setPosition(sf::Vector2f(elements.back()->getPosition().x + elements.back()->getSize().x + Theme::MARGIN, elements.back()->getPosition().y));

	elements.push_back(element);
	return element;
}

Element* VerticalLayout::add(Element* element, int id)
{
	return add(element, Alignment::Vertical, id);
}

void VerticalLayout::onStateChanged(State state)
{
	if (state == State::Default)
	{
		if (focused != nullptr)
		{
			focused->setState(State::Default);
			focused = nullptr;
		}
	}
}

int VerticalLayout::onEvent(const sf::Event& event)
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

bool VerticalLayout::focusNextElement()
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

bool VerticalLayout::focusPreviousElement()
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

void VerticalLayout::onMouseMoved(const sf::Vector2f& position)
{
	// Pressed elements still receive mouse move events even when not hovered if mouse is pressed
	// for things like sliders and scrollbars, which might move without the mouse being overtop of them.
	if (focused != nullptr && sf::Mouse::isButtonPressed(Theme::mouse.clickButton))
	{
		focused->onMouseMoved(sf::Vector2f(focused->getPosition().x, focused->getPosition().y));
	}
	else
	{
		for (auto& element : elements)
		{
			if (element->containsPoint(position))
			{
				if (hovered != element)
				{
					// A new element is hovered
					if (hovered != nullptr)
						hovered->setState(State::Default);

					hovered = element;

					// Don't send Hovered state if element is already focused
					if (hovered != focused)
						element->setState(State::Hovered);
				}
				else	// Hovered element was already hovered
					// Hovered element was already hovered
					element->onMouseMoved(position);

				return;
			}
		}

		// No element hovered, remove hovered state
		if (hovered != nullptr)
		{
			hovered->onMouseMoved(position);
			hovered->setState(focused == hovered ? State::Focused : State::Default);
			hovered = nullptr;
		}
	}
}

void VerticalLayout::onMousePressed(const sf::Vector2f& position)
{
	// TODO: focus element on mousePress, not mouseRelease. might only apply to OptionBox
	// TODO: this method gets called more than once, apparently

//	std::cout << "layout on mouse pressed" << std::endl;

	if (hovered != nullptr)
	{
		// Clicked element takes focus with a 'Pressed' state
		focusElement(hovered, State::Pressed);

		// Send event to element
		// FIXME: multiple layout press events (cause of #3)
		hovered->onMousePressed(position);
	}
	// User didn't click on a element, remove focus state
	else if (focused != nullptr)
	{
		focused->setState(State::Default);
		focused = nullptr;
	}
}

void VerticalLayout::onMouseReleased(const sf::Vector2f& position)
{
	if (focused != nullptr)
	{
		// Send event to the focused element
		focused->onMouseReleased(position);
		focused->setState(State::Focused);
	}
}

void VerticalLayout::onMouseWheelMoved(int delta)
{
	if (focused != nullptr)
		focused->onMouseWheelMoved(delta);
}

void VerticalLayout::onKeyPressed(const sf::Keyboard::Key& key)
{
	// TODO: if in a text box, focus next element on return
	// TODO: make this more versatile

	if (key == Theme::nextWidgetKey || (key == sf::Keyboard::Key::Tab && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)))
	{
		if (!focusNextElement())
			focusNextElement();
	}
	else if (key == Theme::previousWidgetKey || key == sf::Keyboard::Key::Tab)
	{
		if (!focusPreviousElement())
			focusPreviousElement();
	}
	else if (focused != nullptr)
	{
		focused->onKeyPressed(key);
	}
}

void VerticalLayout::onKeyReleased(const sf::Keyboard::Key& key)
{
	if (focused != nullptr)
		focused->onKeyReleased(key);
}

void VerticalLayout::onTextEntered(const sf::Uint32& unicode)
{
	if (focused != nullptr)
		focused->onTextEntered(unicode);
}

bool VerticalLayout::focusElement(Element* element, State state)
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

void VerticalLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setSize(getSize());
	shape.setPosition(getPosition());
	target.draw(shape, states);

	for (const auto element : elements)
		target.draw(*element, states);
}

}
