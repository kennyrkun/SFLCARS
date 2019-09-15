#ifndef THEME_HPP
#define THEME_HPP

#include <map>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>

// TODO: make this a static namespace

class Theme
{
public:
	// Load the GUI global font from a file
	static bool loadFont(const std::string& path);
	// Load the GUI global font from an already loaded font.
	static bool loadFont(const sf::Font* font);
	static const sf::Font& getFont();

	// Load the GUI spritesheet from a file
	// debug: load the texture's debug strip.
	static bool loadTexture(const std::string& path, bool debug = false);
	// Load the GUI spritesheet from an already loaded texture.
	// debug: load the texture's debug strip.
	static bool loadTexture(const sf::Texture* texture, bool debug = false);
	static const sf::Texture& getTexture();

	// Widget height based on text size
	static float getBoxHeight();

	// Height of a line of text
	static float getLineSpacing();

	static sf::Color hexToRgb(std::string hexcolor);

	static size_t textCharacterSize;

	// Properties of visual text
	struct TextStyle
	{
		sf::Color default; // regular text
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

#endif // !THEME_HPP
