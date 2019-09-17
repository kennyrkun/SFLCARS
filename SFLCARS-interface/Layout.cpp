#include "Layout.hpp"

namespace sflcars
{

Layout::Layout(Display* display) : parentDisplay(display)
{
}

Layout::~Layout()
{

}

Button* Layout::addButton(const std::string& text)
{
	Button* button = new Button(text);
	return button;
}

TextBar* Layout::addTextBar(const std::string& text)
{
	TextBar* bar = new TextBar(text);
	return bar;
}

Element* Layout::addElement(Element* element)
{
	return element;
}

void Layout::onStateChanged(State state)
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

void Layout::onMouseMoved(const sf::Vector2f& position)
{
	// Pressed elements still receive mouse move events even when not hovered if mouse is pressed
	// Example: moving a slider's handle
	// TODO: Theme::interactMouseButton
	// TODO: Theme::contextMouseButton
	if (focused != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		focused->onMouseMoved(sf::Vector2f(position.x - focused->getPosition().x, position.y - focused->getPosition().y));
	}
	else
	{
		for (auto& element : parentDisplay->getElements())
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
					{
						element->setState(State::Hovered);
					}
				}
				else
				{
					// Hovered element was already hovered
					element->onMouseMoved(position);
				}

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

void Layout::onMousePressed(const sf::Vector2f& position)
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

void Layout::onMouseReleased(const sf::Vector2f& position)
{
	if (focused != nullptr)
	{
		// Send event to the focused element
		focused->onMouseReleased(position);
		focused->setState(State::Focused);
	}
}

void Layout::onMouseWheelMoved(int delta)
{
	if (focused != nullptr)
		focused->onMouseWheelMoved(delta);
}

void Layout::onKeyPressed(const sf::Keyboard::Key& key)
{
	// TODO: if in a text box, focus next element on return
	// TODO: make this more versatile

	/*
	if (key == Theme::nextWidgetKey || (key == sf::Keyboard::Key::Tab && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)))
		if (!focusNextWidget())
			focusNextWidget();
	else if (key == Theme::previousWidgetKey || key == sf::Keyboard::Key::Tab)
		if (!focusPreviousWidget())
			focusPreviousWidget();
	else*/ if (focused != nullptr)
		focused->onKeyPressed(key);
}

void Layout::onKeyReleased(const sf::Keyboard::Key& key)
{
	if (focused != nullptr)
		focused->onKeyReleased(key);
}

void Layout::onTextEntered(const sf::Uint32& unicode)
{
	if (focused != nullptr)
		focused->onTextEntered(unicode);
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

		// Apply focus to element
		if (element->isSelectable())
		{
			focused = element;
			element->setState(state);
			return true;
		}
	}

	return false;
}

}
