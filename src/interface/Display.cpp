#include "Display.hpp"

#include "../SFLCARS.hpp"

#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

Display::Display(SFLCARS* application, const sf::VideoMode& size, const sf::Vector2i& position, const int id) : application(application), id(id)
{
	sf::ContextSettings context;
	context.antialiasingLevel = 1;

	window = new sf::RenderWindow(size, "SFLCARS", sf::Style::Default, context);
    window->setPosition(position);

	std::cout << "created Display" << id << std::endl;
}

Display::~Display()
{
	std::cout << "destroyed Display" << id << std::endl;
}

void Display::setPadding(float padding)
{
	this->padding = padding;
}

float Display::getPadding()
{
	return 0.0f;
}

Element* Display::addElement(Element* element, Layout align, int id)
{
	std::cout << "[display" << this->id << "] adding element with id " << id << " to display" << this->id << std::endl;

	element->setParent(this);
	element->setID(id);

	element->setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	element->setPosition(sf::Vector2f(padding, padding)); // HACK: get it to calculate it's geometry before we start moving things

	if (elements.empty())
		element->setPosition(sf::Vector2f(padding, padding));
	else
		if (align == Layout::Vertical)
			element->setPosition(sf::Vector2f(padding, elements.back()->getPosition().y + elements.back()->getSize().y + padding));
		else if (align == Layout::Horizontal)
			element->setPosition(sf::Vector2f(elements.back()->getPosition().x + elements.back()->getSize().x + padding, elements.back()->getPosition().y));

	elements.push_back(element);
	return element;
}

int Display::onEvent(const sf::Event& event)
{
	for (auto& x : elements)
	{
		// TODO: test events for subwindows

		switch (event.type)
		{
		case sf::Event::MouseMoved:
		{
			sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			x->onMouseMoved(mouse);
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				x->onMousePressed(mouse);
			}
			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				x->onMouseReleased(mouse);
			}
			break;
		}
		case sf::Event::MouseWheelMoved:
			x->onMouseWheelMoved(event.mouseWheel.delta);
			break;
		case sf::Event::KeyPressed:
			x->onKeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			x->onKeyReleased(event.key.code);
			break;
		case sf::Event::TextEntered:
			x->onTextEntered(event.text.unicode);
			break;
		default:
			break;
		}
	}

	if (triggered != nullptr)
	{
		int id = triggered->getID();
		triggered = nullptr;
		return id;
	}

	return -1;
}

int Display::HandleEvents()
{
    sf::Event event;
    if (window->isOpen())
    {
        window->pollEvent(event);

        if (event.type == sf::Event::EventType::Closed)
            window->close();
        else if (event.type == sf::Event::EventType::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
        }

		int id = onEvent(event);

		if (id >= 0)
			return id;
    }
}

void Display::Update()
{

}

void Display::Draw()
{
    window->clear();

	for (size_t i = 0; i < elements.size(); i++)
		window->draw(*elements[i]);

    window->display();
}
