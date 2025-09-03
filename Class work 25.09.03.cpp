#include <SFML/Graphics.hpp>;

using namespace sf;
using namespace std;

Color MAIN_COLOR(57, 62, 173, 0);
float speed = 4.f;
int main()
{
	bool isright = true;
	RenderWindow window(VideoMode({700,700}), "SFML");

	Vertex figure[] =
	{
		{{100,100}, Color::Green, {0,0}},
		{{55,0}, Color::Blue, {0,0}},
		{{145,0}, Color::Red, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{55,0}, Color::Blue, {0,0}},
		{{0,55}, Color::Red, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{0,55}, Color::Red, {0,0}},
		{{0,145}, Color::Blue, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{0,145}, Color::Blue, {0,0}},
		{{55,200}, Color::Red, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{55,200}, Color::Red, {0,0}},
		{{145,200}, Color::Blue, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{145,200}, Color::Blue, {0,0}},
		{{200,145}, Color::Red, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{200,145}, Color::Red, {0,0}},
		{{200,55}, Color::Blue, {0,0}},

		{{100,100}, Color::Green, {0,0}},
		{{200,55}, Color::Blue, {0,0}},
		{{145,0}, Color::Red, {0,0}}

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

	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
		}
		window.clear(Color::White);
		window.draw(figure, 24, PrimitiveType::Triangles);
		window.display();
	}


	return 0;
}
