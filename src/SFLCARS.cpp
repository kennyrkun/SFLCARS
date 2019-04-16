#include "SFLCARS.hpp"

Display& SFLCARS::newDisplay(const sf::VideoMode& size, const sf::Vector2f& position)
{
    Display newDisplay(size, position);
    displays.push_back(newDisplay);
    return displays.back();
}

void SFLCARS::HandleEvents()
{
    for (int i = 0; i < displays.size(); i++)
        displays[i].HandleEvents();
}

void SFLCARS::Update()
{
    for (int i = 0; i < displays.size(); i++)
        displays[i].Draw();
}

void SFLCARS::Draw()
{
    for (int i = 0; i < displays.size(); i++)
        displays[i].Draw();
}
