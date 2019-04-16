#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Element.hpp"

// This is a base class for all Buttons.
// It 
class Button : public Element
{
public:
	std::string string;

	sf::RectangleShape box;
};

#endif // !BUTTON_HPP