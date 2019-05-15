#ifndef TEXT_BAR_HPP
#define TEXT_BAR_HPP

#include "Bar.hpp"

#include "../utility/RoundRectangle.hpp"

class TextBar : public Bar
{
public:
	TextBar(std::string text);

	void updateSize(const sf::Vector2f& newSize) override;
	
	void setText(std::string text) { this->text.setString(text); }
	std::string getText() { return text.getString(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void reposition() override;

	sf::Text text;
	sf::Font font;
};

#endif // !TEXT_BAR_HPP