#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "utility/RoundRectangle.hpp"

#include "SFLCARS.hpp"
#include "interface/TextBar.hpp"

int main()
{
	SFLCARS* lcars = new SFLCARS;
	Display* display = lcars->newDisplay(sf::VideoMode(600, 400), sf::Vector2i(100, 100));

	TextBar bar("SFLCARS");
	TextBar bar2("bar2");
	TextBar bar3("bar3");

	display->addElement(&bar);
	display->addElement(&bar2);
	display->addElement(&bar3);

	while (lcars->isRunning())
	{
		lcars->HandleEvents();
		lcars->Update();
		lcars->Draw();
	}

	delete lcars;

	/*
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFLCARS");

	sf::Font font;
	font.loadFromFile("./interface/resources/fonts/Okuda.otf");

	t.setFont(font);
	t.setString("SFLCARS");
	t.setCharacterSize(36);

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("./interface/resources/sounds/beep.ogg"))
		std::cerr << "failed to load audio file" << std::endl;

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("./interface/resources/sounds/beep2.ogg"))
		std::cerr << "failed to load audio file" << std::endl;

	std::vector<sf::Sound> sounds;

	sf::Sound beep;
	beep.setBuffer(buffer);
	beep.setVolume(50);

	updatePositions();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::EventType::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));

				windowWidth = event.size.width;
				windowHeight = event.size.height;

				updatePositions();
			}
			else if (event.type == sf::Event::EventType::MouseButtonPressed)
			{
				sf::Sound beep;
				beep.setBuffer(buffer);
				beep.setVolume(50);
				sounds.push_back(beep);
				sounds.back().play();
			}
			else if (event.type == sf::Event::EventType::KeyPressed)
			{
				sf::Sound beep;
				beep.setBuffer(buffer2);
				beep.setVolume(50);
				sounds.push_back(beep);
				sounds.back().play();
			}
		}

		window.clear();
		window.draw(s1);
		window.draw(ss1);
		window.draw(s2);
		window.draw(s3);
		window.draw(ss3);
		window.draw(t);
		window.display();
	}
	*/
}
