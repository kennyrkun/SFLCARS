#ifndef SFLCARS_VERTICAL_LAYOUT_HPP
#define SFLCARS_VERTICAL_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include <vector>

namespace sflcars
{

class Display;
class Element;

class VerticalLayout : sf::Drawable
{
public:
	VerticalLayout(Display* display);
	~VerticalLayout();

	void setDisplay(Display* display);
	Display* getDisplay() const;

	void setSize(const sf::Vector2f& newSize);
	sf::Vector2f getSize() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;
	
	Element* add(Element* element, int id = -1);

	int onEvent(const sf::Event& event);

	bool focusNextElement();
	bool focusPreviousElement();

protected:
	void onStateChanged(State state);

	bool focusElement(Element* element, State state);

	void onMouseMoved(const sf::Vector2f& position);
	void onMousePressed(const sf::Vector2f& position);
	void onMouseReleased(const sf::Vector2f& position);
	void onMouseWheelMoved(int delta);
	void onKeyPressed(const sf::Keyboard::Key& key);
	void onKeyReleased(const sf::Keyboard::Key& key);
	void onTextEntered(const sf::Uint32& unicode);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<Element*> elements;

	Display* display;

	sf::Vector2f size;
};

}

#endif // !SFLCARS_VERTICAL_LAYOUT_HPP
