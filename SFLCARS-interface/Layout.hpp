#ifndef SFLCARS_LAYOUT_HPP
#define SFLCARS_LAYOUT_HPP

#include "Element.hpp"

#include <vector>

namespace sflcars
{

class Display;
class HorizontalLayout;
class VerticalLayout;

class Layout : public Element
{
public:
	Layout(Display* display);
	~Layout();

	void setDisplay(Display* display);
	Display* getDisplay() const;

	void setSize(const sf::Vector2f& newSize);
	sf::Vector2f getSize() const;

	void setPosition(const sf::Vector2f& newPosition) override;
	sf::Vector2f getPosition() const override;

	VerticalLayout* addVerticalLayout();
	HorizontalLayout* addHorizontalLayout();

	virtual Element* add(Element* element, int callbackID = -1) = 0;

	Element* push(Element* element);

	int onEvent(const sf::Event& event);

	bool focusNextElement();
	bool focusPreviousElement();

protected:
	friend class Element;
	friend class HorizontalLayout;
	friend class VerticalLayout;

	bool focusElement(Element* element, State state);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void recomputeGeometry() = 0;

	void onMouseMoved(const sf::Vector2f& position);
	void onMousePressed(const sf::Vector2f& position);
	void onMouseReleased(const sf::Vector2f& position);
	void onMouseWheelMoved(int delta);
	void onKeyPressed(const sf::Keyboard::Key& key);
	void onKeyReleased(const sf::Keyboard::Key& key);
	void onTextEntered(const sf::Uint32& unicode);
	//void onWindowResized(sf::Event::SizeEvent size);

	Element* triggered = nullptr;
	Element* focused = nullptr;
	Element* hovered = nullptr;

	Display* display;

private:
	std::vector<Element*> elements;
	sf::Vector2f size;
	sf::Vector2f position;
};

}

#endif // !SFLCARS_LAYOUT_HPP
