#include "SFLCARS.hpp"

Display* SFLCARS::newDisplay(const sf::VideoMode& size, const sf::Vector2i& position)
{
	Display* newDisplay = new Display(size, position, -1);
	displays.push_back(newDisplay);

	return displays.back();
}

void SFLCARS::HandleEvents()
{
    for (int i = 0; i < displays.size(); i++)
        displays[i]->HandleEvents();
}

void SFLCARS::Update()
{
	if (displays.empty())
		running = false;
	else
		for (int i = 0; i < displays.size(); i++)
	        displays[i]->Draw();
}

void SFLCARS::Draw()
{
    for (int i = 0; i < displays.size(); i++)
        displays[i]->Draw();
}
