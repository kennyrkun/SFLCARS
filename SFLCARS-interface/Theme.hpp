#ifndef SFLCARS_THEME_HPP
#define SFLCARS_THEME_HPP

#include <SFML/Graphics.hpp>

#include <string>

// TODO: make this a static namespace

namespace sflcars
{

class Theme
{
public:
	// Load the GUI global font from a file
	static bool loadFont(const std::string& path);
	// Load the GUI global font from an already loaded font.
	static bool loadFont(const sf::Font* font);

	static const sf::Font& getFont();

	// Widget height based on text size
	static float getBoxHeight();

	// Height of a line of text
	static float getLineSpacing();

	static sf::Color hexToRgb(std::string hexcolor);

	// TODO: add upper and lower bounds to this
	// int lower: the lower boundary for colour
	// int upper: the upper boundary for colour
	// bool single: if r g and b should be the same number
	static sf::Color getRandomColor(int lower = 100, int upper = 255, bool single = false);

	static size_t textCharacterSize;

	// Properties of visual text
	struct TextStyle
	{
		sf::Color normal; // regular text
		sf::Color hovered; // text when hovered
		sf::Color focused; // text when focused
		sf::Color pressed; // text when pressed
	};

	// TODO: Text Highlight Color
	// TODO: Text Edit Highlight Color

	// Used for text by itself.
	static TextStyle label;
	// Used for text in buttons
	static TextStyle button;
	// Used for text in InputBoxes
	static TextStyle input;

	struct MouseInput
	{
		sf::Mouse::Button clickButton = sf::Mouse::Button::Left;
		sf::Mouse::Button contextButton = sf::Mouse::Button::Right;
	};

	static MouseInput mouse;

	static sf::Color windowBgColor;

	static float borderSize; // I think this is unused, but normally it would be the size of lines around things like buttons and sliders
//	static float minWidgetWidth; // Don't know what this is

	static float PADDING; // Spacing inside widget
	static float MARGIN;  // Spacing between widgets

	// TODO: more keys for stuff
//	static sf::Keyboard::Key returns = sf::Keyboard::Key::Return;
//	static sf::Keyboard::Key firstWidget = sf::Keyboard::Key::Home;
	static sf::Keyboard::Key previousWidgetKey;
	static sf::Keyboard::Key nextWidgetKey;
	//	static sf::Keyboard::Key lastWidget = sf::Keyboard::Key::End;
	//	static sf::Keyboard::Key back = sf::Keyboard::Key::BackSpace | sf::Keyboard::Key::Esc;
	//	static sf::Keyboard::Key cancel = sf::Keyboard::Key::Esc;

	static bool triggerCallbacksOnRelease;

private:
	static sf::Font    m_font;
};

}

#endif // !SFLCARS_THEME_HPP
