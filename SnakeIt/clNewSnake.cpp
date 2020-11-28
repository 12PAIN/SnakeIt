#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int direction, num = 4;

struct Snake
{
	int x, y;
} s[100];

void Tick()
{
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;

		if (direction == 0) s[0].y += 1;
		if (direction == 1) s[0].x -= 1;
		if (direction == 2) s[0].x += 1;
		if (direction == 3) s[0].y -= 1;
	}
}

int main()
{
	RenderWindow window(VideoMode(w, h), "Snake The Game");

	Texture t1, t2;
	t1.loadFromFile("Textures/white.png");
	t2.loadFromFile("Textures/red.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);

	Clock clock;
	float timer = 0, delay = 0.1;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (timer > delay)
		{
			timer = 0;
			Tick();
		}

		//////////draw////////
		window.clear();

		for (int i = 0; i < N;i++)
			for (int j = 0; j < M;j++)
			{
				sprite1.setPosition(i * size, j * size); window.draw(sprite1);
			}


		window.display();
	}

	return 0;
}