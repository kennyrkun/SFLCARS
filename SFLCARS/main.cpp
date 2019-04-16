#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "utility/RoundRectangle.hpp"

const float edgePadding = 20.0f;
const float padding = 10.0f;

int windowWidth = 600;
int windowHeight = 400;

float width = 0.0f;
float height = 0.0f;

const float barEdgeWidth = 50;
const float barHeight = 35;

sf::RoundedRectangleShape s1;
sf::RectangleShape ss1;

sf::RectangleShape s2;

sf::RoundedRectangleShape s3;
sf::RectangleShape ss3;

sf::Text t;

class Element
{

};

class Bar : public Element
{
public:
	Bar(const std::string& name)
	{

	}


};

class LCARS
{
public:
	LCARS(int instanceID = 0)
	{

	}

	~LCARS()
	{

	}

	void addBar(Bar bar)
	{

	}

private:
};

void updatePositions()
{
	width = windowWidth - (edgePadding * 2);
	height = windowHeight - (edgePadding * 2);

	s1.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	s1.setCornerPointCount(16);
	s1.setCornersRadius(16);

	ss1.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	s2.setSize(sf::Vector2f(windowWidth - ((edgePadding * 2) + (barEdgeWidth * 2) + (padding * 3) + t.getGlobalBounds().width), barHeight));

	s3.setSize(sf::Vector2f(barEdgeWidth, barHeight));
	s3.setCornerPointCount(16);
	s3.setCornersRadius(16);

	ss3.setSize(sf::Vector2f(barEdgeWidth / 2, barHeight));

	s1.setPosition(edgePadding, edgePadding);
	ss1.setPosition(edgePadding + (barEdgeWidth / 2), edgePadding);
	t.setPosition(s1.getPosition().x + s1.getSize().x + padding, edgePadding - 7);
	s2.setPosition(t.getPosition().x + t.getGlobalBounds().width + padding, edgePadding);
	s3.setPosition(s2.getPosition().x + s2.getSize().x + padding, edgePadding);
	ss3.setPosition(s3.getPosition().x, edgePadding);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFLCARS");

	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Okuda.otf");

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
}