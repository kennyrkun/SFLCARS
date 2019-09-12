#include "SFLCARS.hpp"
#include "interface/TextBar.hpp"
#include "interface/Button.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int calculator()
{
	SFLCARS* lcars = new SFLCARS;
	Display* display = lcars->newDisplay(sf::VideoMode(600, 400), sf::Vector2i(100, 100));

	display->setPadding(5);

	TextBar bar("CALCULATOR");

	Bar placeholderforcurrentequationandstuff;

	display->addElement(&bar);
	display->addElement(&placeholderforcurrentequationandstuff);

	Button rad("Rad");
	Button deg("Deg");
	Button inv("Inv");
	Button sin("sin");
	Button cos("cos");
	Button tan("tan");
	Button pi("pi");
	Button e("e");
	Button exp("EXP");
	Button ans("ans");
	Button xy("x^y");
	Button sqrt("sqrt");
	Button log("log");
	Button ln("ln");
	Button x("x!");

	Button leftParenthesis("(", sf::Keyboard::Key::LBracket);
	Button rightParenthesis(")", sf::Keyboard::Key::RBracket);
	Button percent("%");
	Button clear("C", sf::Keyboard::Key::C);

	Button seven("7", sf::Keyboard::Key::Numpad7);
	Button eight("8", sf::Keyboard::Key::Numpad8);
	Button nine("9", sf::Keyboard::Key::Numpad9);
	Button divide("/", sf::Keyboard::Key::Divide);

	Button four("4", sf::Keyboard::Key::Numpad4);
	Button five("5", sf::Keyboard::Key::Numpad5);
	Button six("6", sf::Keyboard::Key::Numpad6);
	Button multiply("X", sf::Keyboard::Multiply);

	Button one("1", sf::Keyboard::Key::Numpad1);
	Button two("2", sf::Keyboard::Key::Numpad2);
	Button three("3", sf::Keyboard::Key::Numpad3);
	Button subtract("-", sf::Keyboard::Key::Subtract);

	Button zero("0", sf::Keyboard::Key::Numpad0);
	Button decimal(".", sf::Keyboard::Key::Delete);
	Button equals("=", {sf::Keyboard::Key::Return, sf::Keyboard::Key::Equal });
	Button add("+", sf::Keyboard::Key::Add);

	display->addElement(&rad);
	display->addElement(&deg, ElementAlignment::Horizontal);
	display->addElement(&x, ElementAlignment::Horizontal);

	display->addElement(&leftParenthesis, ElementAlignment::Horizontal);
	display->addElement(&rightParenthesis, ElementAlignment::Horizontal);
	display->addElement(&percent, ElementAlignment::Horizontal);
	display->addElement(&clear, ElementAlignment::Horizontal);

	display->addElement(&inv);
	display->addElement(&sin, ElementAlignment::Horizontal);
	display->addElement(&ln, ElementAlignment::Horizontal);

	display->addElement(&seven, ElementAlignment::Horizontal);
	display->addElement(&eight, ElementAlignment::Horizontal);
	display->addElement(&nine, ElementAlignment::Horizontal);
	display->addElement(&divide, ElementAlignment::Horizontal);

	display->addElement(&pi);
	display->addElement(&cos, ElementAlignment::Horizontal);
	display->addElement(&log, ElementAlignment::Horizontal);

	display->addElement(&four, ElementAlignment::Horizontal);
	display->addElement(&five, ElementAlignment::Horizontal);
	display->addElement(&six, ElementAlignment::Horizontal);
	display->addElement(&multiply, ElementAlignment::Horizontal);

	display->addElement(&e);
	display->addElement(&tan, ElementAlignment::Horizontal);
	display->addElement(&sqrt, ElementAlignment::Horizontal);

	display->addElement(&one, ElementAlignment::Horizontal);
	display->addElement(&two, ElementAlignment::Horizontal);
	display->addElement(&three, ElementAlignment::Horizontal);
	display->addElement(&subtract, ElementAlignment::Horizontal);

	display->addElement(&ans);
	display->addElement(&exp, ElementAlignment::Horizontal);
	display->addElement(&xy, ElementAlignment::Horizontal);

	display->addElement(&zero, ElementAlignment::Horizontal);
	display->addElement(&decimal, ElementAlignment::Horizontal);
	display->addElement(&equals, ElementAlignment::Horizontal);
	display->addElement(&add, ElementAlignment::Horizontal);

	while (lcars->isRunning())
	{
		lcars->HandleEvents();
		lcars->Update();
		lcars->Draw();
	}

	delete lcars;

	return 0;
}

int main()
{
	calculator();
	return EXIT_SUCCESS;

	SFLCARS* lcars = new SFLCARS;
	Display* display = lcars->newDisplay(sf::VideoMode(600, 400), sf::Vector2i(100, 100));

	TextBar bar("SFLCARS");
	TextBar bar2("bar2");
	TextBar bar3("bar3");

	Button button("button1");
	Button button2("button2");
	Button button3("button3");
	Button button4("button4");
	Button button5("button5");

	display->addElement(&bar);
	display->addElement(&button);
	display->addElement(&button2);
	display->addElement(&button3);

	display->addElement(&bar2);
	display->addElement(&button4);

	display->addElement(&bar3);
	display->addElement(&button5);

	while (lcars->isRunning())
	{
		lcars->HandleEvents();
		lcars->Update();
		lcars->Draw();
	}

	delete lcars;

	return EXIT_SUCCESS;
}
