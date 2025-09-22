#include <SFML/Graphics.hpp>;
#include <iostream>;
#include <Math.h>;
#include <map>

using namespace sf;
using namespace std;

int randint(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

const Font font("Inkfree.ttf");
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 5;
const int MAP_TILE_SIZE = 70;
char MAP[MAP_HEIGHT][MAP_WIDTH+1] =
{
	"          ",
	"          ",
	"          ",
	"          ",
	"gggggggggg"
};

void draw_map(RenderWindow &window, Sprite groundSprite, map<char, Sprite> &spriteSheet)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			auto sprite = spriteSheet.find(MAP[i][j]);
			if (sprite != spriteSheet.end())
			{
				*(sprite->second).setPosition({ float(j * 70), float(i * 70) });
				groundSprite.setPosition({ float(j * 70), float(i * 70) });
				window.draw(groundSprite);
			}
		}
}

int score = 0;

Vector2f getRandomDiamondPosition()
{
	while (true)
	{
		int x = randint(0, MAP_WIDTH - 1);

		for (int y = MAP_HEIGHT - 1; y >= 0; y--)
		{
			if (MAP[y][x] == 'g')
			{
				int offset = randint(-2, 2);
				int targetY = y + offset;

				if (targetY >= 0 && targetY < MAP_HEIGHT)
				{
					return Vector2f(x * 70.f, targetY * 70.f);
				}
			}
		}
	}
}



void checkCollision(Sprite& player, bool& isJumping)
{
	FloatRect playerRect = player.getGlobalBounds();
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			if (MAP[i][j] == 'g')
			{
				FloatRect tileRect = FloatRect({ float(j * 70), float(i * 70) }, { 70.f, 70.f });
				auto intersection = playerRect.findIntersection(tileRect);
				if (intersection.has_value())
				{
					Vector2f sepapationVector = { 0.f,0.f };
					FloatRect interRect = intersection.value();
					if (interRect.size.x < interRect.size.x)
					{
						if (playerRect.position.x < tileRect.position.x)
							sepapationVector = { -interRect.size.x, 0.f };
						else
							sepapationVector = { interRect.size.x, 0.f };
					}
					else
					{
						if (playerRect.position.y < tileRect.position.y)
						{
							sepapationVector = { 0.f, -interRect.size.y };
							isJumping = false;
						}
						else
							sepapationVector = { 0.f, interRect.size.y };
					}
					player.move(sepapationVector);
					playerRect = player.getGlobalBounds();
				}
			}
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode({ 700,350 }), "SFML");

	Texture player;
	player.loadFromFile("p1_front.png");

	Texture grass;
	grass.loadFromFile("grass.png");

	Sprite sprite_player(player);
	Sprite sprite_grass(grass);

	Texture diamondTexture;
	diamondTexture.loadFromFile("gemBlue.png");
	Sprite diamondSprite(diamondTexture);
	diamondSprite.setScale({ 0.8f, 0.8f });
	diamondSprite.setPosition(getRandomDiamondPosition());

	Texture boxTexture;
	boxTexture.loadFromFile("boxAlt.png");
	Sprite sprite_box(boxTexture);

	Text scoreText(font,"Score: 0",24);
	scoreText.setFillColor(Color::Black);
	scoreText.setPosition({ 10.f, 10.f });

	Vector2f gravity(0, 0.1f);
	Vector2f playerDirection(0.f, 0.f);
	float playerSpeed = 0.001f;
	bool isJumping = true;

	map<char, Sprite> spriteSheet = 
	{
		{'g', sprite_grass},
		{'b', sprite_box}
	};

	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
			if (event->is<Event::KeyPressed>())
				if (event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
					window.close();
		}
		
		window.clear(Color::White);
		draw_map(window, sprite_grass);
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && sprite_player.getPosition().x > 0)
			playerDirection.x -= 0.01f;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && sprite_player.getPosition().x + 70 < window.getSize().x)
			playerDirection.x += 0.01f;
		else
			playerDirection.x = 0;
		sprite_player.move(gravity + playerDirection * playerSpeed);
		checkCollision(sprite_player, isJumping);
		window.draw(sprite_player);
		
		window.display();

	}






	/*Vector2f playerPos = sprite_player.getPosition();
		Vector2f diamondPos = diamondSprite.getPosition();

		float dx = abs(playerPos.x - diamondPos.x);
		float dy = abs(playerPos.y - diamondPos.y);

		if (dx < 50 && dy < 50)
		{
			score++;
			scoreText.setString("Score: " + to_string(score));
			diamondSprite.setPosition(getRandomDiamondPosition());
		}

		window.draw(diamondSprite);
		window.draw(scoreText);*/
	return 0;
}
