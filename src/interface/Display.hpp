#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <vector>

class Display
{
public:
    Display(const sf::VideoMode& size, const sf::Vector2f& position);

    void HandleEvents();
    void Update();
    void Draw();

    const int id;

private:
    sf::RenderWindow window;
};

#endif // !DISPLAY_HPP