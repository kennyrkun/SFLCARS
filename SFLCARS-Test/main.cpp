#include "SFLCARS.hpp"
#include "TextBar.hpp"
#include "Button.hpp"
#include "InputBox.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sflcars;

int calculator()
{
	enum Callback
	{
		cReturn,
		cRad,
		cDeg,
		cInv,
		csin,
		ccos,
		ctan,
		cpi,
		ce,
		cEXP,
		cans,
		cxy,
		csqrt,
		clog,
		cln,
		cx,
	};

	enum ApplicationDisplay
	{
		Calculator,
	};

	sf::SoundBuffer buffer;
	sf::Sound beep;
	buffer.loadFromFile("./resources/sounds/bosun_whistle.ogg");
	beep.setBuffer(buffer);

	SFLCARS* sflcars = new SFLCARS;
	Display* display = sflcars->newDisplay(sf::VideoMode(400, 350), sf::Vector2i(100, 100), ApplicationDisplay::Calculator);

	display->setPadding(5);

//	TextBar bar("CALCULATOR");
	Bar bar;
	display->addElement(&bar);

	InputBox inputBox(330);
	display->addElement(&inputBox);

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
	Button equals("=", { sf::Keyboard::Key::Return, sf::Keyboard::Key::Equal });
	Button add("+", sf::Keyboard::Key::Add);

	display->addElement(&rad, Callback::cRad);
	display->addElement(&deg, Display::Layout::Horizontal, Callback::cDeg);
	display->addElement(&x, Display::Layout::Horizontal, Callback::cx);

	display->addElement(&leftParenthesis, Display::Layout::Horizontal);
	display->addElement(&rightParenthesis, Display::Layout::Horizontal);
	display->addElement(&percent, Display::Layout::Horizontal);
	display->addElement(&clear, Display::Layout::Horizontal);

	display->addElement(&inv, Callback::cInv);
	display->addElement(&sin, Display::Layout::Horizontal, Callback::csin);
	display->addElement(&ln, Display::Layout::Horizontal, Callback::cln);

	display->addElement(&seven, Display::Layout::Horizontal);
	display->addElement(&eight, Display::Layout::Horizontal);
	display->addElement(&nine, Display::Layout::Horizontal);
	display->addElement(&divide, Display::Layout::Horizontal);

	display->addElement(&pi, Callback::cpi);
	display->addElement(&cos, Display::Layout::Horizontal, Callback::ccos);
	display->addElement(&log, Display::Layout::Horizontal, Callback::clog);

	display->addElement(&four, Display::Layout::Horizontal);
	display->addElement(&five, Display::Layout::Horizontal);
	display->addElement(&six, Display::Layout::Horizontal);
	display->addElement(&multiply, Display::Layout::Horizontal);

	display->addElement(&e, Callback::ce);
	display->addElement(&tan, Display::Layout::Horizontal, Callback::ctan);
	display->addElement(&sqrt, Display::Layout::Horizontal, Callback::csqrt);

	display->addElement(&one, Display::Layout::Horizontal);
	display->addElement(&two, Display::Layout::Horizontal);
	display->addElement(&three, Display::Layout::Horizontal);
	display->addElement(&subtract, Display::Layout::Horizontal);

	display->addElement(&ans, Callback::cans);
	display->addElement(&exp, Display::Layout::Horizontal, Callback::cEXP);
	display->addElement(&xy, Display::Layout::Horizontal, Callback::cxy);

	display->addElement(&zero, Display::Layout::Horizontal);
	display->addElement(&decimal, Display::Layout::Horizontal);
	display->addElement(&equals, Display::Layout::Horizontal, Callback::cReturn);
	display->addElement(&add, Display::Layout::Horizontal);

	while (sflcars->isRunning())
	{
		for (auto& event : sflcars->HandleEvents())
		{
			switch (event.displayID)
			{
			case ApplicationDisplay::Calculator:
			{
				switch (event.elementCallbackID)
				{
				case Callback::cReturn:
				{
					inputBox.setText("");
					sf::sleep(sf::milliseconds(10));
					beep.play();
					break;
				}
				case Callback::cans:
					inputBox.addText("ans");
					break;
				case Callback::ccos:
					inputBox.addText("cos(");
					break;
				case Callback::cDeg:
					inputBox.addText("deg(");
					break;
				case Callback::ce:
					inputBox.addText("e(");
					break;
				case Callback::cEXP:
					inputBox.addText("exp(");
					break;
				case Callback::cInv:
					inputBox.addText("inv(");
					break;
				case Callback::cln:
					inputBox.addText("ln(");
					break;
				case Callback::clog:
					inputBox.addText("log(");
					break;
				case Callback::cpi:
					inputBox.addText("pi");
					break;
				case Callback::cRad:
					inputBox.addText("rad(");
					break;
				case Callback::csin:
					inputBox.addText("sin(");
					break;
				case Callback::csqrt:
					inputBox.addText("sqrt(");
					break;
				case Callback::ctan:
					inputBox.addText("tan(");
					break;
				case Callback::cx:
					inputBox.addText("x(");
					break;
				case Callback::cxy:
					inputBox.addText("x^y(");
					break;
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

int notifier()
{
	sf::SoundBuffer buffer;
	sf::Sound whistle;
	buffer.loadFromFile("./resources/sounds/processing2.ogg");
	whistle.setBuffer(buffer);
	whistle.setVolume(50);

	SFLCARS sflcars;
	Display* display = sflcars.newDisplay(sf::VideoMode(600, 400), sf::Vector2i(100, 100));

	InputBox messageBox;
	display->addElement(&messageBox);

	Button send("Send");
	display->addElement(&send, Display::Layout::Horizontal, 1);

	while (sflcars.isRunning())
	{
		for (const auto& event : sflcars.HandleEvents())
		{
			switch (event.elementCallbackID)
			{
			case 1:
			{
				sf::sleep(sf::milliseconds(100));
				messageBox.setText("");
				whistle.play();
				break;
			}
			}
		}

		sflcars.Update();
		sflcars.Draw();
	}

	return 0;
}

int main()
{
	notifier();
	//return EXIT_SUCCESS;

	SFLCARS* lcars = new SFLCARS;
	Display* display = lcars->newDisplay(sf::VideoMode(600, 400), sf::Vector2i(100, 100));
	
	TextBar bar("SFLCARS");
	TextBar bar2("bar2", TextBar::TextAlignment::Right);
	Bar bar3;

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
