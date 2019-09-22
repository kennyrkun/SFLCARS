#include "Display.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <iostream>
#include <random>

namespace sflcars
{

Display::Display(const sf::VideoMode& size, const int id) : id(id)
{
	sf::ContextSettings context;
	context.antialiasingLevel = 1;

	window = new sf::RenderWindow(size, "SFLCARS", sf::Style::Default, context);

	std::cout << "created Display" << id << std::endl;
}

Display::~Display()
{
	clearElements();

	delete window;

	std::cout << "destroyed Display" << id << std::endl;
}

void Display::setPadding(float padding)
{
	Theme::PADDING = padding;
}

float Display::getPadding() const
{
	return Theme::PADDING;
}

bool Display::isOpen() const
{
	return window->isOpen();
}

Element* Display::addElement(Element* element, int id)
{
	return addElement(element, Layout::Vertical, id);
}

Element* Display::addElement(Element* element, Layout align, int id)
{
	std::cout << "[display" << this->id << "] adding element with id " << id << " to display" << this->id << std::endl;

	element->setParent(this);
	element->setID(id);

	element->setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	element->setPosition(sf::Vector2f(Theme::PADDING, Theme::PADDING)); // HACK: get it to calculate it's geometry before we start moving things

	if (elements.empty())
		element->setPosition(sf::Vector2f(Theme::PADDING, Theme::PADDING));
	else
		if (align == Layout::Vertical)
			element->setPosition(sf::Vector2f(Theme::PADDING, elements.back()->getPosition().y + elements.back()->getSize().y + Theme::PADDING));
		else if (align == Layout::Horizontal)
			element->setPosition(sf::Vector2f(elements.back()->getPosition().x + elements.back()->getSize().x + Theme::PADDING, elements.back()->getPosition().y));

	elements.push_back(element);
	return element;
}

std::vector<Element*> Display::getElements() const
{
	return elements;
}

void Display::clearElements()
{
	for (size_t i = 0; i < elements.size(); i++)
		if (elements[i] != nullptr)
			delete elements[i];

	elements.clear();
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
		case sf::Event::Resized:
			x->onWindowResized(event.size);
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

DisplayEvent Display::HandleEvents()
{
	DisplayEvent displayEvent;
	displayEvent.displayID = id;

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

		displayEvent.elementCallbackID = onEvent(event);

		displayEvent.event = event;
		return displayEvent;
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

}
