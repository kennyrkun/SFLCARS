#ifndef SFLCARS_HORIZONTAL_LAYOUT_HPP
#define SFLCARS_HORIZONTAL_LAYOUT_HPP

#include "Layout.hpp"

namespace sflcars
{

class Element;

class HorizontalLayout : public Layout
{
public:
	HorizontalLayout(Display* display);

	Element* add(Element* element, int id = -1);
};

}

#endif // !SFLCARS_HORIZONTAL_LAYOUT_HPP
