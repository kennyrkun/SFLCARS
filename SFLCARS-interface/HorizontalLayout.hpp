#ifndef SFLCARS_LAYOUT_HPP
#define SFLCARS_LAYOUT_HPP

#include "Element.hpp"

#include <vector>

namespace sflcars
{

class Display;

class Layout : public Element
{
public:
	enum class Alignment
	{
		Horizontal,
		Vertical
	};

	Layout(Display* display);
	~Layout();

	void setDisplay(Display* display) override;
	Display* getDisplay() const override;

	void setSize(const sf::Vector2f& newSize);
	sf::Vector2f getSize() const override;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;
	
	Element* add(Element* element, Alignment align, int id = -1);
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

#endif // !SFLCARS_LAYOUT_HPP
