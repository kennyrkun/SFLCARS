#ifdef _WIN32
	#include <SFML/OpenGL.hpp>
#endif

#include "InputBox.hpp"
#include "Theme.hpp"

#include <iostream>

namespace sflcars
{

InputBox::InputBox(float width) : cursorPos(0), maxCharacters(-1), blinkPeriod(1.0f)
{
	box.setSize(sf::Vector2f(width, Theme::getBoxHeight()));
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(Theme::getRandomColor());
	box.setOutlineThickness(Theme::borderSize);

	float offset = Theme::borderSize + Theme::PADDING;
	text.setFont(Theme::getFont());
	text.setPosition(box.getPosition().x + offset, box.getPosition().y + offset);
	text.setFillColor(Theme::input.normal);
	text.setCharacterSize(Theme::textCharacterSize);

	// Build cursor
	cursor.setPosition(offset, offset);
	cursor.setSize(sf::Vector2f(1.f, Theme::getLineSpacing()));
	cursor.setFillColor(Theme::input.normal);
	setCursorPosition(0);

	// TODO: is this necessary?
	setText("");

	setSize(box.getSize());
}

void InputBox::setText(const sf::String& string)
{
	text.setString(string);
	setCursorPosition(string.getSize());

	oldText = text.getString();
}

bool InputBox::isEmpty() const
{
	return text.getString().isEmpty();
}

const sf::String& InputBox::getText() const
{
	return text.getString();
}

void InputBox::setCursorPosition(size_t index)
{
	if (index <= text.getString().getSize())
	{
		cursorPos = index;

		float innerPadding = Theme::borderSize + Theme::PADDING;
		cursor.setPosition(text.findCharacterPos(index).x, box.getPosition().y + innerPadding);
		cursorTimer.restart();

		if (cursor.getPosition().x > getPosition().x + getSize().x - innerPadding)
		{
			std::cout << "shifting text on left" << std::endl;

			// Shift text on left
			float diff = cursor.getPosition().x - (getPosition().x + getSize().x - innerPadding);
			text.move(-diff, 0);
			cursor.move(-diff, 0);
		}
		else if (cursor.getPosition().x < getPosition().x + innerPadding)
		{
			std::cout << "shifting text on right" << std::endl;

			// Shift text on right
			float diff = (getPosition().x + innerPadding) - cursor.getPosition().x;
			text.move(diff, 0);
			cursor.move(diff, 0);
		}

		float textWidth = text.getLocalBounds().width;

		if (text.getPosition().x < innerPadding
			&& text.getPosition().x + textWidth < getSize().x - innerPadding)
		{
			std::cout << "shifting" << std::endl;

			float diff = ((getPosition().x + getSize().x) - innerPadding) - (text.getPosition().x + textWidth);
			text.move(diff, 0);
			cursor.move(diff, 0);

			// If text is smaller than the textbox, force align on left
			if (textWidth < (getSize().x - innerPadding * 2))
			{
				diff = innerPadding - text.getPosition().x;
				text.move(diff, 0);
				cursor.move(diff, 0);
			}
		}
	}
}

size_t InputBox::getCursorPosition() const
{
	return cursorPos;
}

void InputBox::setBlinkPeriod(float period)
{
	blinkPeriod = period;
}

float InputBox::getBlinkPeriod() const
{
	return blinkPeriod;
}

void InputBox::setPosition(const sf::Vector2f& newPosition)
{
	box.setPosition(newPosition);
	float offset = Theme::borderSize + Theme::PADDING;
	text.setPosition(box.getPosition().x + offset, box.getPosition().y + offset);
}

sf::Vector2f InputBox::getPosition() const
{
	return box.getPosition();
}

void InputBox::setSize(const sf::Vector2f& newSize)
{
}

sf::Vector2f InputBox::getSize() const
{
	return box.getSize();
}

void InputBox::onKeyPressed(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		setCursorPosition(cursorPos - 1);
		break;

	case sf::Keyboard::Right:
		setCursorPosition(cursorPos + 1);
		break;

	case sf::Keyboard::BackSpace:
		// Erase character before cursor
		if (cursorPos > 0)
		{
			sf::String string = text.getString();
			string.erase(cursorPos - 1);
			text.setString(string);

			setCursorPosition(cursorPos - 1);
		}
		break;

	case sf::Keyboard::Delete:
		// Erase character after cursor
		if (cursorPos < text.getString().getSize())
		{
			sf::String string = text.getString();
			string.erase(cursorPos);
			text.setString(string);

			setCursorPosition(cursorPos);
		}
		break;

	case sf::Keyboard::Home:
		setCursorPosition(0);
		break;

	case sf::Keyboard::End:
		setCursorPosition(text.getString().getSize());
		break;

	case sf::Keyboard::Return:
		triggerCallback();
		break;

	case sf::Keyboard::Escape:
		text.setString(oldText);
		setCursorPosition(text.getString().getSize());

	default:
		break;
	}
}

void InputBox::onMousePressed(const sf::Vector2f& pos)
{
	for (int i = text.getString().getSize(); i >= 0; --i)
	{
		// Place cursor after the character under the mouse
		sf::Vector2f glyph_pos = text.findCharacterPos(i);
		if (glyph_pos.x <= pos.x)
		{
			setCursorPosition(i);
			break;
		}
	}
}

void InputBox::onTextEntered(const sf::Uint32& unicode)
{
	if (unicode > 30 && (unicode < 127 || unicode > 159))
	{
		sf::String string = text.getString();
		if (maxCharacters == -1 || static_cast<int>(string.getSize() < maxCharacters))
		{
			// Insert character in string at cursor position
			string.insert(cursorPos, unicode);
			text.setString(string);

			setCursorPosition(cursorPos + 1);
		}
	}
}

void InputBox::onStateChanged(State state)
{
	if (state == State::Default)
		oldText = text.getString();

//	box.applyState(state);
}

void InputBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);

#ifdef _WIN32
	// Crop the text with GL Scissor
	glEnable(GL_SCISSOR_TEST);

	sf::Vector2f pos = box.getPosition();
	glScissor((pos.x + Theme::borderSize) - 1, target.getSize().y - (pos.y + getSize().y) + 1, getSize().x, getSize().y - 2);
	target.draw(text, states);

	glDisable(GL_SCISSOR_TEST);
#else
	// draw the text even though it won't have been cut.
	// FIXME: this needs to go away when opengl can be linked
	target.draw(text, states);
#endif

	// Show cursor if focused
	if (isFocused())
	{
		// Make it blink
		float timer = cursorTimer.getElapsedTime().asSeconds();
		if (timer >= blinkPeriod)
			cursorTimer.restart();

		// Updating in the drawing method, deal with it
		sf::Color color = Theme::input.normal;
		color.a = 255 - (255 * timer / blinkPeriod);
		cursor.setFillColor(color);

		target.draw(cursor, states);
	}
}

}
