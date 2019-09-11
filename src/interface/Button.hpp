#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Element.hpp"
#include "../utility/RoundRectangle.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

// TODO: button can be on the left or right side of a bar
// TODO: register listeners for each button or something

// This is a base class for all Buttons.
class Button : public Element
{
public:
	Button();
	Button(const std::string& string);
	Button(const std::string& string, const sf::Keyboard::Key& hotkey);

	void setString(const std::string& string);
	std::string getString() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	bool isDepressed() const;

	void press();
	void release();

	void HandleEvents(const sf::Event& event, sf::RenderWindow& window);

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

	sf::Keyboard::Key hotkey;

	void reposition();

	bool depressed = false;
};

#endif // !BUTTON_HPP