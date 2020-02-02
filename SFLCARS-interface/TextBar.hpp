#ifndef SFLCARS_TEXT_BAR_HPP
#define SFLCARS_TEXT_BAR_HPP

#include "Bar.hpp"
#include "RoundRectangle.hpp"

#include <string>

namespace sflcars
{

class TextBar : public Bar
{
public:
	enum class TextAlignment
	{
		Left,
		Right
		// TODO: middle
	};

	TextBar(const std::string& string, const TextAlignment align = TextAlignment::Left);

	void setAlignment(TextAlignment align);
	TextAlignment getAlignment() const { return align; }

	void setSize(const sf::Vector2f& newSize) override;
	sf::Vector2f getSize() const;

	void setText(const std::string& string) { text.setString(string); }
	std::string getText() const { return text.getString(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void reposition() override;

	TextAlignment align;

	sf::Text text;
};

}

#endif // !SFLCARS_TEXT_BAR_HPP
