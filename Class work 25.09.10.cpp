#include <SFML/Graphics.hpp>;
#include <iostream>;
#include <Math.h>;

using namespace sf;
using namespace std;

const int Map_Width = 10;
const int Map_Height = 7;
const char Map[Map_Height][Map_Width+1] =
{
	"XXXXXXXXXX",
	"X        X",
	"X   XX   X",
	"X   XX   X",
	"X   XX   X",
	"X        X",
	"XXXXXXXXXX",
};

const float TILE_SIZE = 100.f;

Color MAIN_COLOR(57, 62, 173, 0);
/*
bool IsCanMove(CircleShape shape, Vector2f tile)
{
	if (shape.getPosition().x <= tile.x + shape.getRadius() || shape.getPosition().x >= tile.x - shape.getRadius())
		return false;
	else if (shape.getPosition().y <= tile.y + shape.getRadius() || shape.getPosition().y >= tile.y - shape.getRadius())
		return false;
	else
		return true;
}
*/
//bool IsCanMove(CircleShape shape, Vector2f tile)
//{
//
//}

int main()
{
	RenderWindow window(VideoMode({ 1000,700 }), "SFML");

	CircleShape shape(40.f);
	shape.setFillColor(Color::Green);
	shape.setOrigin({ shape.getRadius(), shape.getRadius() });
	shape.setPosition({ 150.f,150.f });

	CircleShape shape1(40.f);
	shape1.setFillColor(Color::Green);
	shape1.setOrigin({ shape.getRadius(), shape.getRadius() });
	shape1.setPosition({ 150.f,150.f });
	float shape_speed = 0.5f;
	Vector2f pos_of_mouse;
	Vector2f pos_of_mouse1;
	Vector2f direction(1, 0);
	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
				window.close();
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Numpad1)
				MAIN_COLOR = Color::Blue;
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Numpad2)
				MAIN_COLOR = Color::Red;
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Numpad3)
				MAIN_COLOR = Color::Black;

			/*if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::D)
				shape.setPosition(shape.getPosition() + Vector2f(10, 0));
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::A)
				shape.setPosition(shape.getPosition() + Vector2f(-10, 0));
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::W)
				shape.setPosition(shape.getPosition() + Vector2f(0, -10));
			if (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::S)
				shape.setPosition(shape.getPosition() + Vector2f(0, 10));*/

			if (event->is<Event::MouseButtonPressed>() && event->getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
			{
				//shape.setPosition((Vector2f)Mouse::getPosition(window));
				pos_of_mouse = (Vector2f)Mouse::getPosition(window);
			}
			if (event->is<Event::MouseButtonPressed>() && event->getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Right)
			{
				//shape.setPosition((Vector2f)Mouse::getPosition(window));
				pos_of_mouse1 = (Vector2f)Mouse::getPosition(window);
				direction = { (pos_of_mouse1.x - shape.getPosition().x) / 150, (pos_of_mouse1.y - shape.getPosition().y) / 150 };
			}
			if (event->is<Event::MouseButtonPressed>() && event->getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Middle)
			{
				shape.setRadius(shape.getRadius() + 1.f);
			}
		}
		window.clear(MAIN_COLOR);
		/*if (Keyboard::isKeyPressed(Keyboard::Key::W))
			shape.move({ 0, -0.5 });
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			shape.move({ 0, 0.5 });
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			shape.move({ -0.5, 0 });
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			shape.move({ 0.5, 0 });*/
		RectangleShape tile({ TILE_SIZE, TILE_SIZE });
		for (int y = 0; y < Map_Height; y++)
			for (int x = 0; x < Map_Width; x++)
			{
				if (Map[y][x] == 'X')
				{
					//RectangleShape tile({ TILE_SIZE, TILE_SIZE });
					tile.setFillColor(Color::Magenta);
					tile.setPosition({ x * TILE_SIZE, y * TILE_SIZE });
					window.draw(tile);
					shape1.setPosition({ tile.getPosition().x + shape.getRadius(), tile.getPosition().y + shape.getRadius() });
				}
				else if (Map[y][x] == ' ')
				{
					if (IsCanMove(shape, tile.getPosition()))
					{
						if (Keyboard::isKeyPressed(Keyboard::Key::W))
							shape.move({ 0, -0.01 });
						if (Keyboard::isKeyPressed(Keyboard::Key::S))
							shape.move({ 0, 0.01 });
						if (Keyboard::isKeyPressed(Keyboard::Key::A))
							shape.move({ -0.01, 0 });
						if (Keyboard::isKeyPressed(Keyboard::Key::D))
							shape.move({ 0.01, 0 });
					}
					else
						cout << "not" << endl;
				}
			}

		/*if (shape.getPosition().x < pos_of_mouse.x)
			shape.move({ shape_speed, 0 });
		if (shape.getPosition().x > pos_of_mouse.x)
			shape.move({ -shape_speed, 0 });
		if (shape.getPosition().y < pos_of_mouse.y)
			shape.move({ 0, shape_speed });
		if (shape.getPosition().y > pos_of_mouse.y)
			shape.move({ 0, -shape_speed });*/
		/*
		if (abs(pos_of_mouse1.x - shape.getPosition().x) > 1 && abs(pos_of_mouse1.y - shape.getPosition().y) > 1)
		{
			shape.setPosition(shape.getPosition() + direction * shape_speed);
		}*/

		
		window.draw(shape);
		window.draw(shape1);
		window.display();
	}


	return 0;
}
