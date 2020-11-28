#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;

const int W = 600;
const int H = 480;
int speed = 4;
bool field[W][H] = { 0 };

struct player
{
	int x, y, dir;
	Color color;
	player(Color c)
	{
		x = rand() % W;
		y = rand() % H;
		color = c;
		dir = rand() % 4;
	}
	void tick()
	{
		if (dir == 0) y += 1;
		if (dir == 1) x -= 1;
		if (dir == 2) x += 1;
		if (dir == 3) y -= 1;

		if (x >= W) x = 0; if (x < 0) x = W - 1;
		if (y >= H) y = 0; if (y < 0) y = H - 1;
	}

	Vector3f getColor()
	{
		return Vector3f(color.r, color.g, color.b);
	}
};

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(W, H), "Tron The Game!");
	window.setFramerateLimit(60);

	Texture texture;
	texture.loadFromFile("Textures/background.jpg");
	Sprite sBackground(texture);

	player p1(Color::Red), p2(Color::Green);

	Sprite sprite;
	RenderTexture t;
	t.create(W, H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear(); t.draw(sBackground);

	bool Game = 1;
	return 0;
}