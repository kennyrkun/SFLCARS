#ifndef SFLCARS_DISPLAY_HPP
#define SFLCARS_DISPLAY_HPP

#include <SFML/Graphics.hpp>

#include <vector>

namespace sflcars
{

class Layout;

struct DisplayEvent
{
	int displayID = -1;

	sf::Event event;
	int elementCallbackID;
};

class Display : public sf::RenderWindow
{
public:
	// TODO: optionally accept an already created renderwindow
	Display(const sf::VideoMode& size, const int id = -1);
	~Display();

	void setLayout(Layout* layout);
	Layout* getLayout() const;

	sf::Vector2f getMousePosition() const;

	void setPadding(float padding);
	float getPadding() const;

	DisplayEvent HandleEvents();
    void Update();
    void DrawLayout();

    const int id;

private:
	Layout* layout;
};

}

#endif // !SFLCARS_DISPLAY_HPP
