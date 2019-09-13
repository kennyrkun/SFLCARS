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

	std::cout << "created Display with id " << id << std::endl;
}

Display::~Display()
{
	std::cout << "destroyed Display  (id " << id << ")" << std::endl;
}

void Display::setPadding(float padding)
{
	this->padding = padding;
}

float Display::getPadding()
{
	return 0.0f;
}

void Display::addElement(Element* element, ElementAlignment align)
{
	std::cout << "adding new element" << std::endl;
	std::cout << elements.size() << std::endl;

	element->setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	element->setPosition(sf::Vector2f(padding, padding)); // HACK: get it to calculate it's geometry before we start moving things

	if (elements.empty())
		element->setPosition(sf::Vector2f(padding, padding));
	else
	{
		if (align == ElementAlignment::Vertical)
		{
			std::cout << "aligning element vertically" << std::endl;
			element->setPosition(sf::Vector2f(padding, elements.back()->getPosition().y + elements.back()->getSize().y + padding));
		}
		else if (align == ElementAlignment::Horizontal)
		{
			std::cout << "aligning element horizontally" << std::endl;
			element->setPosition(sf::Vector2f(elements.back()->getPosition().x + elements.back()->getSize().x + padding, elements.back()->getPosition().y));
		}
	}

	elements.push_back(element);
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

	/*
	if (m_triggered != NULL)
	{
		int id = m_triggered->getID();
		m_triggered = NULL;
		return id;
	}
	*/

	return -1;
}

void Display::HandleEvents()
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

		onEvent(event);
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
