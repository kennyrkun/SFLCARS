#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics.hpp>

class Element : public sf::Drawable
{
public:
	virtual void HandleEvents(const sf::Event& event) = 0;

	int id;
};

#endif // !ELEMENT_HPP
