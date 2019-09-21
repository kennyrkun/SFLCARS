#ifndef SFLCARS_LAYOUT_HPP
#define SFLCARS_LAYOUT_HPP

#include "Display.hpp"

#include "Element.hpp"
#include "Button.hpp"
#include "TextBar.hpp"

namespace sflcars
{

class Layout : public Element
{
public:
	Layout(Display* display);
	~Layout();

	Element* add(Element* element);

	Button* addButton(const std::string& text);
	TextBar* addTextBar(const std::string& text);
	Bar* addBar();

	Element* addElement(Element* element);

	Element* triggered = nullptr;
	Element* focused = nullptr;
	Element* hovered = nullptr;

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

private:
	Display* parentDisplay;
};

}

#endif // !SFLCARS_LAYOUT_HPP
