#include<SFML/Graphics.hpp>
#include<string>

using namespace sf;
using namespace std;

int main(int argc, char const* argv[])
{
	int score = 0;
	float dx, dy, speed = 5;
	dx = 0;
	dy = 0;

	RenderWindow window(VideoMode(300, 400), "Pong");
	window.setFramerateLimit(30);

	Font font;
	font.loadFromFile("Arial.ttf");

	Text text("", font);
	text.setString(to_string(score));
	text.setCharacterSize(20);
	text.setStyle(Text::Bold);
	text.setColor(Color::White);

	RectangleShape ball(Vector2f(10, 10));
	ball.setFillColor(Color::White);
	ball.setPosition(100, 100);

	RectangleShape player(Vector2f(40, 10));
	ball.setFillColor(Color::White);
	ball.setPosition(130, 385);

	while (window.isOpen())
	{
		Vector2f bPos = ball.getPosition();
		Vector2f pPos = player.getPosition();

		if (bPos.x < 0) dx = speed;
		else if (bPos.x > 300 - 10) dx = -speed;
		if (bPos.y < 0) dy = speed;
		else if (bPos.y > 400 - 10)
	}



	while (window.isOpen())
}