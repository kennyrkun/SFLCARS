#include "Element.hpp"
#include <random>

sf::Color Element::getRandomColor(int lower, int upper)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

	return sf::Color(dist(rng), dist(rng), dist(rng));
}

