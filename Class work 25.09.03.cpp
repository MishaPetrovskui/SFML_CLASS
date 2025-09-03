#include <SFML/Graphics.hpp>;
#include <iostream>;

using namespace sf;
using namespace std;

Color MAIN_COLOR(57, 62, 173, 0);
float speed = 100.f;
int main()
{
	bool isright = true;
	bool isright2 = true;
	RenderWindow window(VideoMode({700,700}), "SFML");

	Vertex figure[] =
	{
		{{300 + 50,300}, Color::Green, {0,0}},
		{{255 + 50,200}, Color::Blue, {0,0}},
		{{345 + 50,200}, Color::Red, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{255 + 50,200}, Color::Blue, {0,0}},
		{{200 + 50,255}, Color::Red, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{200 + 50,255}, Color::Red, {0,0}},
		{{200 + 50,345}, Color::Blue, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{200 + 50,345}, Color::Blue, {0,0}},
		{{255 + 50,400}, Color::Red, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{255 + 50,400}, Color::Red, {0,0}},
		{{345 + 50,400}, Color::Blue, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{345 + 50,400}, Color::Blue, {0,0}},
		{{400 + 50,345}, Color::Red, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{400 + 50,345}, Color::Red, {0,0}},
		{{400 + 50,255}, Color::Blue, {0,0}},

		{{300 + 50,300}, Color::Green, {0,0}},
		{{400 + 50,255}, Color::Blue, {0,0}},
		{{345 + 50,200}, Color::Red, {0,0}}

		/*{{100,100}, Color::Red, {0,0}},
		{{0,50}, Color::Red, {0,0}},
		{{0,150}, Color::Red, {0,0}},

		{{100,10}, Color::Red, {0,0}},
		{{0,150}, Color::Red, {0,0}},
		{{100,200}, Color::Red, {0,0}},

		{{100,100}, Color::Red, {0,0}},
		{{100,200}, Color::Red, {0,0}},
		{{200,150}, Color::Red, {0,0}},

		{{100,100}, Color::Red, {0,0}},
		{{200,50}, Color::Red, {0,0}},
		{{200,150}, Color::Red, {0,0}},

		{{100,100}, Color::Red, {0,0}},
		{{200,50}, Color::Red, {0,0}},
		{{100,0}, Color::Red, {0,0}}*/
	};

	CircleShape Circle(20.f);
	Circle.setFillColor(Color::Green);
	Circle.setOutlineColor(Color::Red);
	Circle.setOutlineThickness(10.f);

	CircleShape Circle2(20.f);
	Circle2.setFillColor(Color::Green);
	Circle2.setPosition({700,0});
	Circle2.setOutlineColor(Color::Red);
	Circle2.setOutlineThickness(10.f);

	Vector2f direction(1, 0);
	float timer1 = 0.f;
	Clock clock;

	while (window.isOpen())
	{
		system("cls");
		auto time = clock.restart().asMilliseconds() / 1000.f;

		system("cls");
		cout << 1 / time << "fps" << endl;

		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
		}
		timer1 += time;
		if (timer1 == 2)
		{
			Circle.setFillColor(Color::Green);
		}
		else if (timer1 >= 3)
		{
			Circle.setFillColor(Color::Red);
			timer1 -= 3;
		}

		window.clear(Color::White);
		//window.draw(figure, 24, PrimitiveType::Triangles);
		if (isright)
		{
			Circle.setPosition(Circle.getPosition() + direction * speed * time);
			Circle2.setPosition(Circle2.getPosition() - direction * speed * time);
			if (Circle.getPosition().x >= 650)
			{
				isright = false;
			}
			else if ((Circle.getPosition() - Circle2.getPosition()).length() - (Circle.getRadius() + Circle2.getRadius()) <= 1)
			{
				isright = false;
			}
		}
		else if (!isright)
		{
			Circle.setPosition(Circle.getPosition() - direction * speed * time);
			Circle2.setPosition(Circle2.getPosition() + direction * speed * time);
			if (Circle.getPosition().x <= 1)
			{
				isright = true;
			}
		}
		window.draw(Circle);
		window.draw(Circle2);
		
		window.display();
	}


	return 0;
}
