#ifndef SFLCARS_LAYOUT_HPP
#define SFLCARS_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include <vector>

namespace sflcars
{

class Display;
class Element;
enum class State;

class Layout : sf::Drawable
{
public:
	Layout(Display* display);
	~Layout();

	void setDisplay(Display* display);
	Display* getDisplay() const;

	void setSize(const sf::Vector2f& newSize);
	sf::Vector2f getSize() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;
	
	int onEvent(const sf::Event& event);

	bool focusNextElement();
	bool focusPreviousElement();

protected:
	bool focusElement(Element* element, State state);

	void onMouseMoved(const sf::Vector2f& position);
	void onMousePressed(const sf::Vector2f& position);
	void onMouseReleased(const sf::Vector2f& position);
	void onMouseWheelMoved(int delta);
	void onKeyPressed(const sf::Keyboard::Key& key);
	void onKeyReleased(const sf::Keyboard::Key& key);
	void onTextEntered(const sf::Uint32& unicode);
	void onWindowResized(const sf::Event::SizeEvent& newSize);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Element* triggered;

private:
	std::vector<Element*> elements;

	Display* display;

	sf::Vector2f size;
};

}

#endif // !SFLCARS_LAYOUT_HPP
