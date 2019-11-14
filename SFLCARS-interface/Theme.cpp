#include "Theme.hpp"

#include <random>
#include <iostream>

namespace sflcars
{

ResourceManager Theme::resources;

size_t    Theme::textCharacterSize = 36;
Theme::TextStyle Theme::label = { sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White };
Theme::TextStyle Theme::button;
Theme::TextStyle Theme::input = { sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White };
sf::Color Theme::windowBgColor;
float     Theme::borderSize = 1.0f;
//float     Theme::minWidgetWidth = 86;
float     Theme::PADDING = 1.0f;
float     Theme::MARGIN = 20.0f;
bool Theme::triggerCallbacksOnRelease = true;

sf::Keyboard::Key Theme::nextWidgetKey = sf::Keyboard::Down;
sf::Keyboard::Key Theme::previousWidgetKey = sf::Keyboard::Up;

Theme::MouseInput Theme::mouse;

bool Theme::textAllCaps = true;

bool Theme::loadFont(const std::string& filename)
{
	return resources.loadFont("mainFont", filename) != nullptr;
}

const sf::Font& Theme::getFont()
{
	return *resources.getFont("mainFont");
}

float Theme::getBoxHeight()
{
	return getLineSpacing() + (borderSize * 2) + (PADDING * 2);
}

float Theme::getLineSpacing()
{
	return resources.getFont("mainFont")->getLineSpacing(textCharacterSize);
}

sf::Color Theme::hexToRgb(std::string hexcolor)
{
	// TODO: make this more versatile

//	if (hexcolor.length > 7)
//		return;

//	std::cout << "converting " << hexcolor << std::endl;

	// TODO: improve this
	// put a # in front of the thing because we're stupid and need it
	if (hexcolor[0] != '#')
		hexcolor.insert(0, "#");

	sf::Color color(sf::Color::White);
	if (hexcolor.size() == 7) // #ffffff
	{
		color.r = sf::Uint8( strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16) );
		color.g = sf::Uint8( strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16) );
		color.b = sf::Uint8( strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16) );
	}
	else if (hexcolor.size() == 4) // #fff, shorthand
	{
		color.r = sf::Uint8( strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17 );
		color.g = sf::Uint8( strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17 );
		color.b = sf::Uint8( strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17 );
	}

//	std::cout << "result " << std::to_string(color.r) << ", " << std::to_string(color.g) << ", " << std::to_string(color.b) << std::endl;

	return color;
}

sf::Color Theme::getRandomColor(int lower, int upper, bool single)
{
	// TODO: should these be static?
	// or are they already static because it's a static function?
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

	if (single)
	{
		int i = dist(rng);
		return sf::Color(i, i, i);
	}
	else
		return sf::Color(dist(rng), dist(rng), dist(rng));
}

}
