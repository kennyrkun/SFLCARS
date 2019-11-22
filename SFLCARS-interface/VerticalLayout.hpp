#ifndef SFLCARS_VERTICAL_LAYOUT_HPP
#define SFLCARS_VERTICAL_LAYOUT_HPP

#include "Layout.hpp"

namespace sflcars
{

class Display;
class Element;

class VerticalLayout : public Layout
{
public:
	VerticalLayout(Display* display);

	Element* add(Element* element, int id = -1);

private:
	void recomputeGeometry();
};

}

#endif // !SFLCARS_VERTICAL_LAYOUT_HPP
