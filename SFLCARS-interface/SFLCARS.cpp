#include "SFLCARS.hpp"

#include <iostream>

namespace sflcars
{

SFLCARS::SFLCARS()
{
    running = true;
}

Display* SFLCARS::newDisplay(const sf::VideoMode& size, const sf::Vector2i& position, const int id)
{
	Display* newDisplay = new Display(this, size, position, id);
	displays.push_back(newDisplay);

	return displays.back();
}

std::vector<DisplayEvent> SFLCARS::HandleEvents()
{
	std::vector<DisplayEvent> vector;

	for (auto& display : displays)
		vector.push_back(display->HandleEvents());
	
	return vector;
}

void SFLCARS::Update()
{
	if (displays.empty())
		running = false;
	else
		for (int i = 0; i < displays.size(); i++)
        {
			if (displays[i]->isOpen())
				displays[i]->Update();
            else //TODO: don't delete display unless the display is ready to die
            {
                std::cout << "window is closed, deleting Display" << std::endl;

                Display* d = displays[i];

            	displays.erase(std::remove(displays.begin(), displays.end(), d), displays.end());
                delete d;

                // TODO: remove the entry from the vector
            }
        }
}

void SFLCARS::Draw()
{
    for (int i = 0; i < displays.size(); i++)
        displays[i]->Draw();
}

}
