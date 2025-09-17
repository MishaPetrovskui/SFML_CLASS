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

Vector2f nearestPoint(Vector2f point, RectangleShape rectangle)
{
	float left = rectangle.getPosition().x;
	float right = rectangle.getPosition().x + rectangle.getSize().x;
	float top = rectangle.getPosition().y;
	float bottom = rectangle.getPosition().y + rectangle.getSize().y;
	return { clamp(point.x,left,right), clamp(point.y,top,bottom) };
}
bool isCollide(CircleShape circle, Vector2f point)
{
	return (point - circle.getPosition()).length() - circle.getRadius() <= 0;
}

bool isCollide(CircleShape circle, RectangleShape rectangle)
{
	return isCollide(circle, nearestPoint(circle.getPosition(), rectangle));
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode({ 1200,800 }), "SFML");

	CircleShape circle(50.f);
	circle.setFillColor(Color::Green);
	circle.setOrigin({ circle.getRadius(), circle.getRadius() });
	circle.setPosition({ 300.f,400.f });
	CircleShape indicator(5.f);
	indicator.setFillColor(Color::Red);
	indicator.setOrigin({ indicator.getRadius(), indicator.getRadius() });
	indicator.setPosition({ 0.f,0.f });

	RectangleShape rectangle({ 100.f, 100.f });
	rectangle.setFillColor(Color::Blue);
	rectangle.setPosition((Vector2f)window.getSize() / 2.f - rectangle.getSize() / 2.f);
	Vector2f mousePosition;
	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
			if (event->is<Event::KeyPressed>())
				if (event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
					window.close();
			if (event->is<Event::MouseMoved>())
			{
				mousePosition = (Vector2f)event->getIf<Event::MouseMoved>()->position;
				//direction = ((Vector2f)mousePosition - circle.getPosition()) / 100.f;
			}
		}
		
		window.clear(Color::Black);

		window.draw(rectangle);
		Vector2f direction = ((Vector2f)mousePosition - circle.getPosition()) / 100.f;
		indicator.setPosition(nearestPoint(circle.getPosition(), rectangle));
		circle.move(direction);
		if (isCollide(circle, rectangle))
			circle.move(-direction);

		window.draw(rectangle);

		indicator.setPosition(
			nearestPoint(circle.getPosition(), rectangle)
		);
		window.draw(indicator);
		window.draw(circle);
		
		window.display();

	}


	return 0;
}
