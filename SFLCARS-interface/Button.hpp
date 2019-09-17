#ifndef SFLCARS_BUTTON_HPP
#define SFLCARS_BUTTON_HPP

#include "Element.hpp"
#include "RoundRectangle.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
//#include <functional>

// TODO: button can be on the left or right side of a bar
// TODO: register listeners for each button or something

namespace sflcars
{

// This is a base class for all Buttons.
class Button : public Element
{
public:
	// todo: have fewer constructors
	Button(const std::string& string);
	Button(const std::string& string, const sf::Keyboard::Key& hotkey);
	Button(const std::string& string, std::vector<sf::Keyboard::Key> hotkeys);

	void addHotkey(const sf::Keyboard::Key& key);
	std::vector<sf::Keyboard::Key> getHotkeys() const;

	void setString(const std::string& string);
	std::string getString() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	bool isDepressed() const;

	void press();
	void release();

	void onMousePressed(const sf::Vector2f& position);
	void onMouseReleased(const sf::Vector2f& position);
	void onKeyPressed(const sf::Keyboard::Key& key);
	void onKeyReleased(const sf::Keyboard::Key& key);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Font font;
	sf::Text text;

	sf::SoundBuffer buffer;
	sf::Sound beep;

	sf::RoundedRectangleShape box;

	std::vector<sf::Keyboard::Key> hotkeys;
//	std::function callback;

	void reposition();

	bool depressed = false;
};

}

#endif // !SFLCARS_BUTTON_HPP
