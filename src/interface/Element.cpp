#include "Element.hpp"
#include <random>

void Element::setID(int id)
{
	this->id = id;
}

int Element::getID() const
{
	return id;
}

sf::Color Element::getRandomColor(int lower, int upper)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

	return sf::Color(dist(rng), dist(rng), dist(rng));
}

void Element::setSelectable(bool selectable)
{
	this->selectable = selectable;
}

bool Element::isSelectable() const
{
	return selectable;
}

