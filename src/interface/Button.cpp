#include "Button.hpp"

Button::Button()
{
	font.loadFromFile("./interface/resources/fonts/Okuda.otf");
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(36);

	// suffer
}

Button::Button(const std::string& string)
{
	font.loadFromFile("./interface/resources/fonts/Okuda.otf");
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(36);

	setString(string);

	reposition();
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

void Button::HandleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);

		if (box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			box.setFillColor(sf::Color::Red);
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		box.setFillColor(sf::Color::White);
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
//	text.setPosition(box.getPosition());
}
