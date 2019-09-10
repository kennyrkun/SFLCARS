#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Element.hpp"

enum class ElementAlignment
{
	Horizontal,
	Vertical
};

class Display
{
public:
	Display(const sf::VideoMode& size, const sf::Vector2i& position, const int id);
	~Display();

	void setPadding(float padding);
	float getPadding();

	bool isOpen() { return window->isOpen(); }

	void addElement(Element* element, ElementAlignment align = ElementAlignment::Vertical);

	int onEvent(const sf::Event& event);

    void HandleEvents();
    void Update();
    void Draw();

    const int id;

private:
    sf::RenderWindow* window;

	std::vector<Element*> elements;

	float padding = 20;
};

#endif // !DISPLAY_HPP