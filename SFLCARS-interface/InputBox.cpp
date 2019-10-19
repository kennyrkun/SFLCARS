#ifdef _WIN32
	#include <SFML/OpenGL.hpp>
#endif

#include "InputBox.hpp"
#include "Theme.hpp"

#include <iostream>

float padding = 4;

namespace sflcars
{

InputBox::InputBox(float width) : cursorPos(0), maxCharacters(-1), blinkPeriod(1.0f)
{
	text.setFont(Theme::getFont());
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(36);

	box.setSize(sf::Vector2f(width, Theme::getFont().getLineSpacing(text.getCharacterSize())));
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(Theme::getRandomColor());
	box.setOutlineThickness(-4);

	float outlineThickness = std::abs(box.getOutlineThickness());

	cursor.setSize(sf::Vector2f(2, Theme::getFont().getLineSpacing(text.getCharacterSize()) - (outlineThickness * 2) - (padding * 2)));
	cursor.setFillColor(sf::Color::White);
	setCursorPosition(0);
}

void InputBox::setText(const sf::String& string)
{
	text.setString(string);
	setCursorPosition(string.getSize());

	oldText = text.getString();
}

const sf::String& InputBox::getText() const
{
	return text.getString();
}

void InputBox::addText(const sf::String& string)
{
	setText(getText() + string);
}

bool InputBox::isEmpty() const
{
	return text.getString().isEmpty();
}

void InputBox::setCursorPosition(size_t index)
{
	if (index <= text.getString().getSize())
	{
		cursorPos = index;

		cursor.setPosition(text.findCharacterPos(index).x, box.getPosition().y + std::abs(box.getOutlineThickness()) + padding);
		cursorTimer.restart();

		if (cursor.getPosition().x > getSize().x - padding)
		{
			// Shift text on left
			float diff = cursor.getPosition().x - getSize().x + padding;
			text.move(-diff, 0);
			cursor.move(-diff, 0);
		}
		else if (cursor.getPosition().x < padding)
		{
			// Shift text on right
			float diff = padding - cursor.getPosition().x;
			text.move(diff, 0);
			cursor.move(diff, 0);
		}

		float text_width = text.getLocalBounds().width;

		if (text.getPosition().x < padding
			&& text.getPosition().x + text_width < getSize().x - padding)
		{
			float diff = (getSize().x - padding) - (text.getPosition().x + text_width);
			text.move(diff, 0);
			cursor.move(diff, 0);

			// If text is smaller than the textbox, force align on left
			if (text_width < (getSize().x - padding * 2))
			{
				diff = padding - text.getPosition().x;
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
	text.setPosition(sf::Vector2f(box.getPosition().x - box.getOutlineThickness() + 4, box.getPosition().y + box.getOutlineThickness()));
	setCursorPosition(getCursorPosition());
}

sf::Vector2f InputBox::getPosition() const
{
	return box.getPosition();
}

void InputBox::setSize(const sf::Vector2f& newSize)
{
	return;
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

void InputBox::onMousePressed(const sf::Vector2f& position)
{
	for (int i = text.getString().getSize(); i >= 0; --i)
	{
		// Place cursor after the character; under the mouse
		sf::Vector2f glyph_pos = text.findCharacterPos(i);
		if (glyph_pos.x <= position.x)
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
}

void InputBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);

#ifdef _WIN32
	// Crop the text with GL Scissor
	glEnable(GL_SCISSOR_TEST);

	sf::Vector2f pos = box.getPosition();
	glScissor((pos.x + std::abs(box.getOutlineThickness())) - 1, target.getSize().y - (pos.y + getSize().y), getSize().x - 2, getSize().y);
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
		float timer = cursorTimer.getElapsedTime().asSeconds();
		if (timer >= blinkPeriod)
			cursorTimer.restart();

		// Updating in the drawing method, deal with it
		//sf::Color color = Theme::input.textColor;
		sf::Color color = sf::Color::White;
		color.a = 255 - (255 * timer / blinkPeriod);
		cursor.setFillColor(color);

		target.draw(cursor, states);
	}
}

}
