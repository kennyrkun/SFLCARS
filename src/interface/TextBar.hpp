#ifndef TEXT_BAR_HPP
#define TEXT_BAR_HPP

#include "Bar.hpp"

#include "../utility/RoundRectangle.hpp"

enum class Alignment
{
	Left,
	Right
};

class TextBar : public Bar
{
public:
	TextBar(std::string text, Alignment align = Alignment::Left);

	void setAlignment(Alignment align);
	Alignment getAlignment() { return align; }

	void setSize(const sf::Vector2f& newSize) override;
	sf::Vector2f getSize() override;

	void setText(std::string text) { this->text.setString(text); }
	std::string getText() { return text.getString(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void reposition() override;

	Alignment align;

	sf::Text text;
	sf::Font font;
};

#endif // !TEXT_BAR_HPP
