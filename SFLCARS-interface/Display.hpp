#ifndef SFLCARS_DISPLAY_HPP
#define SFLCARS_DISPLAY_HPP

#include "Element.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace sflcars
{

struct DisplayEvent
{
	int displayID = -1;

	sf::Event event;
	int elementCallbackID;
};

class Display
{
public:
	Display(const sf::VideoMode& size, const sf::Vector2i& position, const int id = -1);
	~Display();

	enum class Layout
	{
		Horizontal,
		Vertical
	};

	void setPadding(float padding);
	float getPadding();

	bool isOpen() { return window->isOpen(); }

	Element* addElement(Element* element, int id = -1);
	Element* addElement(Element* element, Layout align, int id = -1);

	int onEvent(const sf::Event& event);

    DisplayEvent HandleEvents();
    void Update();
    void Draw();

    const int id;
	Element* triggered = nullptr;

private:
    sf::RenderWindow* window;

	std::vector<Element*> elements;

	float padding = 20;
};

}

#endif // !SFLCARS_DISPLAY_HPP
