#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Element.hpp"
#include "../utility/RoundRectangle.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

// TODO: button can be on the left or right side of a bar

// This is a base class for all Buttons.
class Button : public Element
{
public:
	Button();
	Button(const std::string& string);

	void setString(const std::string& string);
	std::string getString() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	void HandleEvents(const sf::Event& event, sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Font font;
	sf::Text text;

	sf::RoundedRectangleShape box;

	void reposition();

	bool depressed = false;
};

#endif // !BUTTON_HPP