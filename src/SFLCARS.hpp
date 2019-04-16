#ifndef LCARS_HPP
#define LCARS_HPP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "interface/Display.hpp"
#include "interface/Element.hpp"

class SFLCARS
{
public:
    Display& newDisplay(const sf::VideoMode& size, const sf::Vector2f& position);

    void HandleEvents();
    void Update();
    void Draw();

private:
    std::vector<Element> elements;

    std::vector<Display> displays;
};

#endif // !LCARS_HPP