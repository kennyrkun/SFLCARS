#ifndef SFLCARS_TEXT_BAR_HPP
#define SFLCARS_TEXT_BAR_HPP

#include "Bar.hpp"

#include "RoundRectangle.hpp"

namespace sflcars
{

class TextBar : public Bar
{
public:
	enum class TextAlignment
	{
		Left,
		Right
	};

	TextBar(std::string text, TextAlignment align = TextAlignment::Left);

	void setAlignment(TextAlignment align);
	TextAlignment getAlignment() { return align; }

	void setSize(const sf::Vector2f& newSize) override;
	sf::Vector2f getSize() const;

	void setText(std::string text) { this->text.setString(text); }
	std::string getText() const { return text.getString(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void reposition() override;

	TextAlignment align;

	sf::Text text;
	sf::Font font;
};

}

#endif // !SFLCARS_TEXT_BAR_HPP
