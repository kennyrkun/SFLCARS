#include "SFLCARS.hpp"
#include "interface/TextBar.hpp"
#include "interface/Button.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
	SFLCARS* lcars = new SFLCARS;
	Display* display = lcars->newDisplay(sf::VideoMode(600, 400), sf::Vector2i(100, 100));

	TextBar bar("SFLCARS");
	TextBar bar2("bar2", Alignment::Right);
	TextBar bar3("bar3");

	Button button("button1");
	Button button2("button2");
	Button button3("button3");
	Button button4("button4");
	Button button5("button5");

	display->addElement(&bar);
	display->addElement(&button);
	display->addElement(&button2);
	display->addElement(&button3);

	display->addElement(&bar2);
	display->addElement(&button4);

	display->addElement(&bar3);
	display->addElement(&button5);

	while (lcars->isRunning())
	{
		lcars->HandleEvents();
		lcars->Update();
		lcars->Draw();
	}

	delete lcars;
}
