#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int main()
{
	RenderWindow window(VideoMode(w, h), "Snake The Game");

	Texture t1, t2;
	t1.loadFromFile("Textures/white.png");
	t2.loadFromFile("Textures/red.png");

	Sprite spritr1(t1);
	Sprite spritr2(t2);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
	}

	return 0;
}