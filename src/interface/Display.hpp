#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Element.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class SFLCARS;

enum class Layout
{
	Horizontal,
	Vertical
};

class Display
{
public:
	Display(SFLCARS* application, const sf::VideoMode& size, const sf::Vector2i& position, const int id);
	~Display();

	void setPadding(float padding);
	float getPadding();

	bool isOpen() { return window->isOpen(); }

	Element* addElement(Element* element, Layout align = Layout::Vertical, int id = -1);

	int onEvent(const sf::Event& event);

    void HandleEvents();
    void Update();
    void Draw();

    const int id;

private:
	SFLCARS* application;

    sf::RenderWindow* window;

	std::vector<Element*> elements;

	float padding = 20;
};

#endif // !DISPLAY_HPP