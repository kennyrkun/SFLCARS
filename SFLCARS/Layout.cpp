#include "Layout.hpp"

Layout::Layout(Display* display) : parentDisplay(display)
{
}

Layout::~Layout()
{

}

Button* Layout::addButton(const std::string& text)
{
	Button* button = new Button(text);
	return button;
}

TextBar* Layout::addTextBar(const std::string& text)
{
	TextBar* bar = new TextBar(text);
	return bar;
}

Element* Layout::addElement(Element* element)
{
	return element;
}
