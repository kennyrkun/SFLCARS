#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Button.hpp"

class TextButton : public Button
{
public:
	std::string string;

	sf::RectangleShape box;
};

#endif // !TEXT_BUTTON_HPP