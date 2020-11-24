#include <SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
#include<ctime>
#include<cstdlib>
#include<random>

using namespace sf;

int SIZE = 30;
int vx = SIZE * SIZE;
int vy = SIZE * 15;
int horizontalline = 30;
int verticalline = 15;
int direction = 2;
int num = 3;

struct
{
	int x, y;
}apple;

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

	if ((snake[0].x == apple.x) && (snake[0].y == apple.y))
	{
		num++;
		apple.x = rand() % 30;
		apple.y = rand() % 15;
	}

	if (snake[0].x > 30)
	{
		snake[0].x = 0;
		snake[0].y = 0;
		num = 3;
	}
	if (snake[0].y > 15)
	{
		snake[0].x = 0;
		snake[0].y = 0;
		num = 3;
	}

	if (snake[0].x < 0)
	{
		snake[0].x = 0;
		snake[0].y = 0;
		num = 3;
	}

	if (snake[0].y < 0)
	{
		snake[0].x = 0;
		snake[0].y = 0;
		num = 3;
	}

	for (int i = 1; i < num; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			snake[0].x = 0;
			snake[0].y = 0;
			num = 3;
		}
	}
}

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(vx, vy), "Snake The Game");
	RectangleShape block;
	RectangleShape blockSnake;
	RectangleShape blockApple;

	Clock clock;
	float chrono = 0;
	float delay = 0.1;

	blockSnake.setSize(Vector2f(SIZE, SIZE));
	blockSnake.setFillColor(Color::Green);// Цвет клетки 
	blockSnake.setOutlineThickness(1);// Толщина линий 
	blockSnake.setOutlineColor(Color::White);// Цвет линий 

	block.setSize(Vector2f(SIZE, SIZE));
	block.setFillColor(Color::Black);// Цвет клетки
	block.setOutlineThickness(1);// Толщина линий 
	block.setOutlineColor(Color::White);// Цвет линий 

	blockApple.setSize(Vector2f(SIZE, SIZE));
	blockApple.setFillColor(Color::Red);// Цвет клетки
	blockApple.setOutlineThickness(1);// Толщина линий 
	blockApple.setOutlineColor(Color::White);// Цвет линий 

	apple.x = rand() % 30;
	apple.y = rand() % 15;

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


			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				direction = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				direction = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				direction = 2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				direction = 3;
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
			for (int i = 0; i < num; i++)
			{
				blockSnake.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
				window.draw(blockSnake);
			}
			blockApple.setPosition(apple.x * SIZE, apple.y * SIZE);
			window.draw(blockApple);
			window.display();
		}
	}
}