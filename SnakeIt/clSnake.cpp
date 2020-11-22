#include <SFML/Graphics.hpp>
#include<iostream>
#include<time.h>

int SIZE = 30;
int vx = SIZE * SIZE;
int vy = SIZE * 15;
int horizontalline = 30;
int verticalline = 15;

int main()
{
	RenderWindow window(VideoMode(vx, vy), "Snake The Game");
	RectangleShape block;
	block.setSize(Vector2f(SIZE, SIZE));
	block.setFillColor(Color::Black);// Цвет фона
	block.setOutlineThickness(1);// Толщина линий 
	block.setOutlineColor(Color::White);// Цвет линий 
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
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