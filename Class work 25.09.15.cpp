#include <SFML/Graphics.hpp>;
#include <iostream>;
#include <Math.h>;

using namespace sf;
using namespace std;

int randint(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

const Font font("Inkfree.ttf");

char Knopka[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode({ 1000,700 }), "SFML");

	int activeButton = 0;
	Text answers[4]
	{
		Text(font, "A", 50),
		Text(font, "B", 50),
		Text(font, "C", 50),
		Text(font, "D", 50)
	};
	int activequestion = 0;
	Text test[5]
	{
		Text(font, "A", 50),
		Text(font, "B", 50),
		Text(font, "C", 50),
		Text(font, "D", 50),
		Text(font, "E", 50)
	};

	for (int i = 0; i < 4; i++)
	{
		if (i == activeButton)
			answers[i].setFillColor(Color::Red);
		answers[i].setPosition({ 50.f, 400.f + (float)(answers[i].getCharacterSize() * i) });
	}
	int correct = 0;

	/*int index = randint(0, 26);
	int clickCount = 0;
	Text text1(font, "Click for " + Knopka[index], 50);
	text1.setString("Clicked: " + to_string(clickCount++) + "times" + "Button: " + Knopka[index]);
	text1.setFillColor(Color::Black);*/
	
	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
			if (event->is<Event::KeyPressed>())
				if (event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
					window.close();
			/*if (event->is<Event::KeyPressed>())
			{
				auto keyEvent = event->getIf<Event::KeyPressed>()->code;
				if (keyEvent == Keyboard::Key::Up)
					text1.setCharacterSize(text1.getCharacterSize()+1);
				if (keyEvent == Keyboard::Key::Down)
					text1.setCharacterSize(text1.getCharacterSize() - 1);
				if (text1.getCharacterSize() < 1)
					text1.setCharacterSize(1);
				if (text1.getCharacterSize() > 300)
					text1.setCharacterSize(300);
			}
			if (event->is<Event::KeyPressed>())
				if (event->getIf<Event::KeyPressed>()->code == (Keyboard::Key)index)
				{					
					index = randint(0, 26);
					text1.setString("Clicked: " + to_string(clickCount++) + "times" + "Button: " + Knopka[index]);
				}*/
			if (event->is<Event::KeyPressed>())
			{
				auto keyEvent = event->getIf<Event::KeyPressed>()->code;
				if (keyEvent == Keyboard::Key::Up)
					activeButton = max(0, activeButton-1);
				if (keyEvent == Keyboard::Key::Down)
					activeButton = min(3, activeButton + 1);
			}
		}
		/*cout << Knopka[index] << endl;
		cout << index << endl;
		if (clickCount < 10)
			text1.setFillColor(Color::Green);
		else if (clickCount >= 11 && clickCount < 30)
			text1.setFillColor(Color::Yellow);
		else if (clickCount > 30)
			text1.setFillColor(Color::Red);

		text1.setOrigin({ text1.getLocalBounds().size.x / 2.f, text1.getLocalBounds().size.y / 2.f });
		text1.setPosition({(window.getSize().x / 2.f), (window.getSize().y / 2.f) });*/
		window.clear(Color::White);

		if (activequestion == 0)
		{
			test[activequestion].setString("Question 1: How many legs does a cat have?");
			answers[0].setString("A. 2");
			answers[1].setString("B. 3");
			answers[2].setString("C. 4");
			answers[3].setString("D. 5");
			window.draw(test[activequestion]);
			for (int i = 0; i < 4; i++)
			{
				if (i == activeButton)
					answers[i].setFillColor(Color::Red);
				else
					answers[i].setFillColor(Color::Black);
				window.draw(answers[i]);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				if (activeButton == 2)
				{
					correct++;
					cout << "Correct!" << endl;
				}
				else
					cout << "Wrong!" << endl;
				activequestion++;
				activeButton = 0;
			}
		}
		else if (activequestion == 1)
		{
			for (int i = 0; i < 5; i++)
			{
				if (i == activeButton)
					test[i].setFillColor(Color::Red);
				else
					test[i].setFillColor(Color::Black);
				window.draw(test[i]);
			}
		}

		window.display();
	}


	return 0;
}           
