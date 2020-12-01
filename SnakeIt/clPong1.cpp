#include<SFML/Graphics.hpp>
#include<string>
#include "clPong1.h"

using namespace sf;
using namespace std;

void clPong::Pong()
{
	int score = 0;
	float dx, dy, speed = 5;
	dx = 0;
	dy = 0;

	RenderWindow window(VideoMode(300, 400), "Pong");
	window.setFramerateLimit(30);

	Font font;
	font.loadFromFile("../Font/Arial.ttf");

	Text text("", font);
	text.setString(to_string(score));
	text.setCharacterSize(20);
	text.setStyle(Text::Bold);
	text.setFillColor(Color::White);

	RectangleShape ball(Vector2f(10, 10));
	ball.setFillColor(Color::White);
	ball.setPosition(100, 100);

	RectangleShape player(Vector2f(40, 10));
	player.setFillColor(Color::White);
	player.setPosition(130, 385);

	while (window.isOpen())
	{
		Vector2f bPos = ball.getPosition();
		Vector2f pPos = player.getPosition();

		if (bPos.x < 0) dx = speed;
		else if (bPos.x > 300 - 10) dx = -speed;
		if (bPos.y < 0) dy = speed;
		else if (bPos.y > 400 - 10)
		{
			dy = 0;
			dx = 0;
		}

		if (bPos.x >= pPos.x && bPos.x <= pPos.x + 40)
			if (bPos.y >= pPos.y - 10)
			{
				score++;
				text.setString(to_string(score));
				dy = -speed;
			}
		ball.move(dx, dy);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			dx = speed;
			dy = speed;
			score = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (pPos.x > 0) player.move(-speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (pPos.x < 300 - 40) player.move(speed, 0);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		window.clear();
		window.draw(ball);
		window.draw(player);
		window.draw(text);
		window.display();
	}
}
