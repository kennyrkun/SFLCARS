#ifndef SFLCARS_INPUT_BOX_HPP
#define SFLCARS_INPUT_BOX_HPP

#include "Element.hpp"

// TODO: support lots of text
// TODO: setRows(int rowCount);
//		 amount of rows in the editor

// TODO: support text editing stuff
// Undo
// Redo
// Select
// Select Word
// Select All
// Move selected

namespace sflcars
{

 // Single-line text editor.
class InputBox : public Element
{
public:
	InputBox(float width = 200.f);

	void setText(const sf::String& string);
	const sf::String& getText() const;

	void addText(const sf::String& string);

	bool isEmpty() const;

	void setCursorPosition(size_t index);
	size_t getCursorPosition() const;

	void setBlinkPeriod(float period);
	float getBlinkPeriod() const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	void setSize(const sf::Vector2f& newSize);
	sf::Vector2f getSize() const;

//protected:
	// Callbacks
	void onKeyPressed(const sf::Keyboard::Key& key);
	void onMousePressed(const sf::Vector2f& position);
	void onTextEntered(const sf::Uint32& unicode);

	// FIXME: sometimes these keep the hovered state
	void onStateChanged(State state);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape box;

	std::string oldText;
	sf::Text    text;
	sf::Font	font;

	mutable sf::RectangleShape cursor;
	mutable sf::Clock  cursorTimer;
	float			   blinkPeriod;
	// TODO: add cursor delay (.25s)

	size_t maxCharacters;
	size_t cursorPos;
};

}

#endif // !SFLCARS_INPUT_BOX_HPP
