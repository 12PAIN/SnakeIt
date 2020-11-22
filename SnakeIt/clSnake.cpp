#include <SFML/Graphics.hpp>
#include<iostream>
#include<time.h>

using namespace sf;
int SIZE = 30;
int vx = SIZE * SIZE;
int vy = SIZE * 15;
int horizontalline = 30;
int verticalline = 15;
int direction = 1;
int num = 3;

struct Snake
{
	int x, y;
} snake[100];

void gameAction()
{
	for (int i = num; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (direction == 0)
	{
		snake[0].y += 1;
	}
	else if (direction == 1)
	{
		snake[0].x -= 1;
	}
	else if (direction == 2)
	{
		snake[0].x += 1;
	}
	else if (direction == 3)
	{
		snake[0].y -= 1;
	}
}

int main()
{
	RenderWindow window(VideoMode(vx, vy), "Snake The Game");
	RectangleShape block;

	Clock clock;
	float chrono = 0;
	float delay = 0.1;

	block.setSize(Vector2f(SIZE, SIZE));
	block.setFillColor(Color::Black);// Цвет фона
	block.setOutlineThickness(1);// Толщина линий 
	block.setOutlineColor(Color::White);// Цвет линий 

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		chrono += time;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			if (chrono > delay)
			{
				chrono = 0;
				gameAction();
			}

			window.clear();
			for (int i = 0; i < verticalline; i++)//Прорисовка клеточек
			{
				for (int j = 0; j < horizontalline; j++)
				{
					block.setPosition(j * SIZE, i * SIZE);
					window.draw(block);
				}
			}

			window.display();
		}
	}
}