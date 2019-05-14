#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Element.hpp"

class Display
{
public:
	Display(const sf::VideoMode& size, const sf::Vector2i& position, const int id);
	~Display();

	void addElement(Element* element);

    void HandleEvents();
    void Update();
    void Draw();

    const int id;

    sf::RenderWindow* window;
private:

	std::vector<Element*> elements;
};

#endif // !DISPLAY_HPP