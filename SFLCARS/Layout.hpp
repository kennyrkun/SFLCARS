#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "Display.hpp"

#include "Element.hpp"
#include "Button.hpp"
#include "TextBar.hpp"

class Layout : public Element
{
public:
	Layout(Display* display);
	~Layout();

	Button* addButton(const std::string& text);
	TextBar* addTextBar(const std::string& text);

	Element* addElement(Element* element);

private:
	Display* parentDisplay;
};

#endif // !LAYOUT_HPP
