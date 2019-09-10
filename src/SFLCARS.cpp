#include "SFLCARS.hpp"

SFLCARS::SFLCARS()
{
    running = true;
}

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
