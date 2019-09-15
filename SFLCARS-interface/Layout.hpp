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

	Button* addButton(const std::string& text);
	TextBar* addTextBar(const std::string& text);

	Element* addElement(Element* element);

private:
	Display* parentDisplay;
};

}

#endif // !SFLCARS_LAYOUT_HPP
