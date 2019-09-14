#include "SFLCARS.hpp"
#include "interface/TextBar.hpp"
#include "interface/Button.hpp"
#include "interface/Spacer.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int calculator()
{
	enum Callback
	{
		Return,
	};

	enum ApplicationDisplay
	{
		Calculator,
	};

	sf::SoundBuffer buffer;
	sf::Sound beep;
	buffer.loadFromFile("./interface/resources/sounds/error_input1.ogg");
	beep.setBuffer(buffer);

	SFLCARS* sflcars = new SFLCARS;
	Display* display = sflcars->newDisplay(sf::VideoMode(400, 350), sf::Vector2i(100, 100), ApplicationDisplay::Calculator);

	display->setPadding(5);

	TextBar bar("CALCULATOR");
	display->addElement(&bar);

	Spacer spacer(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
	display->addElement(&spacer);
	spacer.setSize(sf::Vector2f(100, 100));

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
	Button clear("C", { sf::Keyboard::Key::C, sf::Keyboard::Key::Escape });

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
	Button decimal(".", sf::Keyboard::Key::Period);
	Button equals("=", {sf::Keyboard::Key::Return, sf::Keyboard::Key::Equal });
	Button add("+", sf::Keyboard::Key::Add);

	display->addElement(&rad);
	display->addElement(&deg, Layout::Horizontal);
	display->addElement(&x, Layout::Horizontal);

	display->addElement(&leftParenthesis, Layout::Horizontal);
	display->addElement(&rightParenthesis, Layout::Horizontal);
	display->addElement(&percent, Layout::Horizontal);
	display->addElement(&clear, Layout::Horizontal);

	display->addElement(&inv);
	display->addElement(&sin, Layout::Horizontal);
	display->addElement(&ln, Layout::Horizontal);

	display->addElement(&seven, Layout::Horizontal);
	display->addElement(&eight, Layout::Horizontal);
	display->addElement(&nine, Layout::Horizontal);
	display->addElement(&divide, Layout::Horizontal);

	display->addElement(&pi);
	display->addElement(&cos, Layout::Horizontal);
	display->addElement(&log, Layout::Horizontal);

	display->addElement(&four, Layout::Horizontal);
	display->addElement(&five, Layout::Horizontal);
	display->addElement(&six, Layout::Horizontal);
	display->addElement(&multiply, Layout::Horizontal);

	display->addElement(&e);
	display->addElement(&tan, Layout::Horizontal);
	display->addElement(&sqrt, Layout::Horizontal);

	display->addElement(&one, Layout::Horizontal);
	display->addElement(&two, Layout::Horizontal);
	display->addElement(&three, Layout::Horizontal);
	display->addElement(&subtract, Layout::Horizontal);

	display->addElement(&ans);
	display->addElement(&exp, Layout::Horizontal);
	display->addElement(&xy, Layout::Horizontal);

	display->addElement(&zero, Layout::Horizontal);
	display->addElement(&decimal, Layout::Horizontal);
	display->addElement(&equals, Layout::Horizontal, Callback::Return);
	display->addElement(&add, Layout::Horizontal);

	while (sflcars->isRunning())
	{
		for (auto& x : sflcars->HandleEvents())
		{
			switch (x.first)
			{
			case ApplicationDisplay::Calculator:
			{
				switch (x.second)
				{
				case Callback::Return:
				{
					sf::sleep(sf::milliseconds(10));
					beep.play();
					break;
				}
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}

		sflcars->Update();
		sflcars->Draw();
	}

	delete sflcars;

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
