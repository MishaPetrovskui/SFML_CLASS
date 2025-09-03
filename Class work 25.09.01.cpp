#include <SFML/Graphics.hpp>;

using namespace sf;
using namespace std;

Color MAIN_COLOR(57, 62, 173, 0);
float speed = 4.f;
int main()
{
	bool isright = true;
	RenderWindow window(VideoMode({200,200}), "SFML");

	Vertex figure[] =
	{
		{{100,100}, Color::Red, {0,0}},
		{{120,120}, Color::Red, {0,0}},
		{{80,120}, Color::Red, {0,0}},
		{{100,100}, Color::Red, {0,0}}
	};

	CircleShape Circle(50);
	Circle.setPosition({ 0,0 });
	Circle.setFillColor(Color::Red);

	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
		}
		window.clear(MAIN_COLOR);
		//window.draw(figure, 4, PrimitiveType::Triangles);
		if (isright)
		{
			Circle.setPosition(Circle.getPosition() + Vector2f(speed, 0));
			if (Circle.getPosition().x >= 100)
			{
				isright = false;
			}
		}
		else
		{
			Circle.setPosition(Circle.getPosition() - Vector2f(speed, 0));
			if (Circle.getPosition().x <= 1)
			{
				isright = true;
			}
		}
		
		window.draw(Circle);
		window.display();
	}


	return 0;
}
