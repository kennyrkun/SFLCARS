#ifndef SFLCARS_HPP
#define SFLCARS_HPP

#include "interface/Element.hpp"
#include "interface/Display.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class SFLCARS
{
public:
    SFLCARS();

    Display* newDisplay(const sf::VideoMode& size, const sf::Vector2i& position, const int id = -1);

    std::vector<std::pair<int, int>> HandleEvents();
    void Update();
    void Draw();

	bool isRunning() { return running; }

private:
    std::vector<Element> elements;

    std::vector<Display*> displays;

	bool running = false;
};

#endif // !SFLCARS_HPP