#ifndef SFLCARS_SFLCARS_HPP
#define SFLCARS_SFLCARS_HPP

#include "Element.hpp"
#include "Display.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace sflcars
{

class SFLCARS
{
public:
    SFLCARS();

    Display* newDisplay(const sf::VideoMode& size, const sf::Vector2i& position, const int id = -1);

    std::vector<DisplayEvent> HandleEvents();
    void Update();
    void Draw();

	bool isRunning() { return running; }

private:
    std::vector<Element> elements;

    std::vector<Display*> displays;

	bool running = false;
};

}

#endif // !SFLCARS_SFLCARS_HPP
