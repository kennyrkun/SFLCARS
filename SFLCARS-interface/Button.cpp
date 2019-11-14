#include "Button.hpp"
#include "Theme.hpp"

#include <random>
#include <cctype>

namespace sflcars
{

Button::Button(const std::string& string)
{
	text.setFont(Theme::getFont());
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(Theme::textCharacterSize);

	box.setFillColor(Theme::getRandomColor());

	std::string sounds[4] = { "beep", "beep2", "beep3", "beep4" };

	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);
	std::random_device dev;
	std::mt19937 rng(dev());

	int i = dist(rng);

	buffer.loadFromFile(Theme::resources.getResourceDirectory() + "/sounds/" + sounds[i] + ".ogg");
	beep.setBuffer(buffer);

	// TODO: if Theme::textAllCaps == true, make text uppercase
	setString(string);
}

Button::Button(const std::string& string, const sf::Keyboard::Key& hotkey) : Button(string)
{
	hotkeys.push_back(hotkey);
}

Button::Button(const std::string& string, std::vector<sf::Keyboard::Key> hotkeys) : Button(string)
{
	this->hotkeys = hotkeys;
}

void Button::addHotkey(const sf::Keyboard::Key& key)
{
	hotkeys.push_back(key);
}

std::vector<sf::Keyboard::Key> Button::getHotkeys() const
{
	return hotkeys;
}

void Button::setString(const std::string& string)
{
	text.setString(string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, (text.getGlobalBounds().height / 2) + 12));

	// probably update sizes and such
}

std::string Button::getString() const
{
	return text.getString();
}

void Button::setPosition(const sf::Vector2f& newPosition)
{
	box.setPosition(newPosition);

	reposition();
}

sf::Vector2f Button::getPosition() const
{
	return box.getPosition();
}

sf::Vector2f Button::getSize() const
{
	return sf::Vector2f(box.getGlobalBounds().width, box.getGlobalBounds().height);
}

bool Button::isDepressed() const
{
	return depressed;
}

void Button::enable()
{
	enabled = true;
	box.setFillColor(Theme::getRandomColor());
}

void Button::disable()
{
	enabled = false;
	sf::Color t = text.getFillColor(), b = box.getFillColor();
	text.setFillColor(sf::Color(t.r, t.g, t.b, 100));
	box.setFillColor(sf::Color(b.r, b.g, b.b, 100));
}

bool Button::isEnabled() const
{
	return enabled;
}

void Button::press()
{
	depressed = true;
	box.setFillColor(sf::Color::Red);
	beep.play();
}

void Button::release()
{
	depressed = false;
	box.setFillColor(Theme::getRandomColor());
}

void Button::onMousePressed(const sf::Vector2f& position)
{
	if (!enabled)
		return;

	if (box.getGlobalBounds().contains(position))
	{
		press();

		if (!Theme::triggerCallbacksOnRelease)
			triggerCallback();
	}
}

void Button::onMouseReleased(const sf::Vector2f& position)
{
	if (!enabled)
		return;

	if (depressed)
	{
		release();

		if (Theme::triggerCallbacksOnRelease)
			if (box.getGlobalBounds().contains(position))
				triggerCallback();
	}
}

void Button::onKeyPressed(const sf::Keyboard::Key& key)
{
	if (!enabled)
		return;

	if (std::find(hotkeys.begin(), hotkeys.end(), key) != hotkeys.end())
	{
		if (!depressed)
		{
			press();

			//if (callbackOnPress) 
				//triggerCallback();
		}
	}
}

void Button::onKeyReleased(const sf::Keyboard::Key& key)
{
	if (!enabled)
		return;

	if (depressed)
		if (std::find(hotkeys.begin(), hotkeys.end(), key) != hotkeys.end())
		{
			release();
			triggerCallback();
		}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(text, states);
}

void Button::reposition()
{
	sf::FloatRect size = text.getGlobalBounds();

	box.setSize(sf::Vector2f(size.width + 30, 35));
	box.setCornerPointCount(16);
	box.setCornersRadius(16);

	text.setPosition(sf::Vector2f(box.getPosition().x + (box.getSize().x / 2), box.getPosition().y + (box.getSize().y / 2)));
}

}
