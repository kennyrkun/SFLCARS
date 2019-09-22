#include <Layout.hpp>
#include <Display.hpp>
#include <TextBar.hpp>
#include <Button.hpp>
#include <InputBox.hpp>

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

	display->setPadding(5);

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

	layout->add(&rad, Callback::cRad);
	layout->add(&deg, Layout::Alignment::Horizontal, Callback::cDeg);
	layout->add(&x, Layout::Alignment::Horizontal, Callback::cx);

	layout->add(&leftParenthesis, Layout::Alignment::Horizontal);
	layout->add(&rightParenthesis, Layout::Alignment::Horizontal);
	layout->add(&percent, Layout::Alignment::Horizontal);
	layout->add(&clear, Layout::Alignment::Horizontal);

	layout->add(&inv, Callback::cInv);
	layout->add(&sin, Layout::Alignment::Horizontal, Callback::csin);
	layout->add(&ln, Layout::Alignment::Horizontal, Callback::cln);

	layout->add(&seven, Layout::Alignment::Horizontal);
	layout->add(&eight, Layout::Alignment::Horizontal);
	layout->add(&nine, Layout::Alignment::Horizontal);
	layout->add(&divide, Layout::Alignment::Horizontal);

	layout->add(&pi, Callback::cpi);
	layout->add(&cos, Layout::Alignment::Horizontal, Callback::ccos);
	layout->add(&log, Layout::Alignment::Horizontal, Callback::clog);

	layout->add(&four, Layout::Alignment::Horizontal);
	layout->add(&five, Layout::Alignment::Horizontal);
	layout->add(&six, Layout::Alignment::Horizontal);
	layout->add(&multiply, Layout::Alignment::Horizontal);

	layout->add(&e, Callback::ce);
	layout->add(&tan, Layout::Alignment::Horizontal, Callback::ctan);
	layout->add(&sqrt, Layout::Alignment::Horizontal, Callback::csqrt);

	layout->add(&one, Layout::Alignment::Horizontal);
	layout->add(&two, Layout::Alignment::Horizontal);
	layout->add(&three, Layout::Alignment::Horizontal);
	layout->add(&subtract, Layout::Alignment::Horizontal);

	layout->add(&ans, Callback::cans);
	layout->add(&exp, Layout::Alignment::Horizontal, Callback::cEXP);
	layout->add(&xy, Layout::Alignment::Horizontal, Callback::cxy);

	layout->add(&zero, Layout::Alignment::Horizontal);
	layout->add(&decimal, Layout::Alignment::Horizontal);
	layout->add(&equals, Layout::Alignment::Horizontal, Callback::cReturn);
	layout->add(&add, Layout::Alignment::Horizontal);

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
		display->Draw();
	}

	return 0;
}

int notifier()
{
	sf::SoundBuffer buffer_start;
	sf::SoundBuffer buffer_loop;
	sf::SoundBuffer buffer_end;
	sf::Sound whistle;
	whistle.setVolume(50);
	buffer_start.loadFromFile("./resources/sounds/processing2_1.ogg");
	buffer_loop.loadFromFile("./resources/sounds/processing2_2.ogg");
	buffer_end.loadFromFile("./resources/sounds/processing2_3.ogg");

	whistle.setBuffer(buffer_start);

	Display* display = new Display(sf::VideoMode(600, 400));

	Layout* layout = display->getLayout();

	InputBox messageBox;
	layout->add(&messageBox);

	Button send("Send");
	layout->add(&send, Layout::Alignment::Horizontal, 1);

	while (display->isOpen())
	{
		DisplayEvent event = display->HandleEvents();

		switch (event.elementCallbackID)
		{
		case 1:
		{
			sf::sleep(sf::milliseconds(100));
			messageBox.setText("");
			whistle.play();

			while (whistle.getStatus() != sf::Sound::Status::Stopped)
				continue;

			whistle.setBuffer(buffer_loop);
			whistle.setLoop(true);
			whistle.play();

			sf::sleep(sf::seconds(1));

			whistle.setBuffer(buffer_end);
			whistle.setLoop(false);
			whistle.play();

			break;
		}
		}

		display->Update();
		display->Draw();
	}

	return 0;
}

int main()
{
	notifier();
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
