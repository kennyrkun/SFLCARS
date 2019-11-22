#include <Layout.hpp>
#include <Display.hpp>
#include <TextBar.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <HorizontalLayout.hpp>

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

	Display* display = new Display(sf::VideoMode(400, 350), ApplicationDisplay::Calculator);
	Layout* layout = display->getLayout();

	//	TextBar bar("CALCULATOR");
	Bar bar;
	layout->add(&bar);

	InputBox inputBox(330);
	layout->add(&inputBox);

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

	sflcars::HorizontalLayout* row1 = layout->addHorizontalLayout();
	row1->add(&rad, Callback::cRad);
	row1->add(&deg, Callback::cDeg);
	row1->add(&x, Callback::cx);

	row1->add(&leftParenthesis);
	row1->add(&rightParenthesis);
	row1->add(&percent);
	row1->add(&clear);

	sflcars::HorizontalLayout* row3 = layout->addHorizontalLayout();
	row3->add(&inv, Callback::cInv);
	row3->add(&sin, Callback::csin);
	row3->add(&ln, Callback::cln);

	row3->add(&seven);
	row3->add(&eight);
	row3->add(&nine);
	row3->add(&divide);

	sflcars::HorizontalLayout* row5 = layout->addHorizontalLayout();
	row5->add(&pi, Callback::cpi);
	row5->add(&cos, Callback::ccos);
	row5->add(&log, Callback::clog);

	row5->add(&four);
	row5->add(&five);
	row5->add(&six);
	row5->add(&multiply);

	sflcars::HorizontalLayout* row7 = layout->addHorizontalLayout();
	row7->add(&e, Callback::ce);
	row7->add(&tan, Callback::ctan);
	row7->add(&sqrt, Callback::csqrt);

	row7->add(&one);
	row7->add(&two);
	row7->add(&three);
	row7->add(&subtract);

	sflcars::HorizontalLayout* row9 = layout->addHorizontalLayout();
	row9->add(&ans, Callback::cans);
	row9->add(&exp, Callback::cEXP);
	row9->add(&xy, Callback::cxy);

	row9->add(&zero);
	row9->add(&decimal);
	row9->add(&equals, Callback::cReturn);
	row9->add(&add);

	display->setSize(sf::Vector2u(layout->getSize().x, layout->getSize().y));

	while (display->isOpen())
	{
		DisplayEvent event = display->HandleEvents();

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

		display->Update();

		display->clear();
		display->DrawLayout();
		display->display();
	}

	return 0;
}

int main()
{
	sflcars::Theme::loadFont("fonts/Okuda.otf");

	calculator();
	return EXIT_SUCCESS;

	Display* display = new Display(sf::VideoMode(600, 400));

	Layout* layout = display->getLayout();

	TextBar bar("SFLCARS");
	TextBar bar2("bar2", TextBar::TextAlignment::Right);
	Bar bar3;

	Button button("button1");
	Button button2("button2");
	Button button3("button3");
	Button button4("button4");
	Button button5("button5");

	layout->add(&bar);
	layout->add(&button);
	layout->add(&button2);
	layout->add(&button3);

	layout->add(&bar2);
	layout->add(&button4);

	layout->add(&bar3);
	layout->add(&button5);

	return EXIT_SUCCESS;
}
