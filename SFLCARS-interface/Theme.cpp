#include "Theme.hpp"

size_t    Theme::textCharacterSize = 12;
Theme::TextStyle Theme::label;
Theme::TextStyle Theme::button;
Theme::TextStyle Theme::input;
sf::Color Theme::windowBgColor;
float     Theme::borderSize = 1.f;
//float     Theme::minWidgetWidth = 86;
float     Theme::PADDING = 1.f;
float     Theme::MARGIN = 7.f;
bool Theme::triggerCallbacksOnRelease = true;

sf::Keyboard::Key Theme::nextWidgetKey = sf::Keyboard::Down;
sf::Keyboard::Key Theme::previousWidgetKey = sf::Keyboard::Up;

sf::Font Theme::m_font;

bool Theme::loadFont(const std::string& filename)
{
	return m_font.loadFromFile(filename);
}

bool Theme::loadFont(const sf::Font* font)
{
	if (font)
	{
		m_font = *font;
		return true;
	}

	return false;
}

const sf::Font& Theme::getFont()
{
	return m_font;
}

float Theme::getBoxHeight()
{
	return getLineSpacing() + borderSize * 2 + PADDING * 2;
}

float Theme::getLineSpacing()
{
	return m_font.getLineSpacing(textCharacterSize);
}

sf::Color Theme::hexToRgb(std::string hexcolor)
{
	// TODO: make this more versatile

//	if (hexcolor.length > 7)
//		return;

//	std::cout << "converting " << hexcolor << std::endl;

	// TODO: improve this
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
