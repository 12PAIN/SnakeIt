#include <SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
#include "clSnake.h"
#include <Windows.h>
#include <string>


using namespace sf;

void clSnake::gameAction()
{	
	
	

	for (int i = num; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	if (gameOver != 1) {
		if (direction == 0)
		{
			snake[0].y += 1;
			Sleep(50);
		}
		else if (direction == 1)
		{
			snake[0].x -= 1;
			Sleep(50);
		}
		else if (direction == 2)
		{
			snake[0].x += 1;
			Sleep(50);
		}
		else if (direction == 3)
		{
			snake[0].y -= 1;
			Sleep(50);
		}
	}
	else {

	}
	if ((snake[0].x == apple.x) && (snake[0].y == apple.y))
	{
		num++;
		apple.x = rand() % 30;
		apple.y = rand() % 15;
	}

	if (snake[0].x >= 30)
	{
		gameOver = 1;
		
	}
	if (snake[0].y >= 15)
	{
		gameOver = 1;
		
	}

	if (snake[0].x < 0)
	{
		gameOver = 1;
		
	}

	if (snake[0].y < 0)
	{
		gameOver = 1;
		
	}

	for (int i = 1; i < num; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			gameOver = 1;
			
		}
	}
}

void clSnake::Snake(int WIDTH, int HEIGHT)
{

	restart = 0; gameOver = 0;
	do {

		for (int i = 0; i < 100; i++) {
			snake[i].x = 15;
			snake[i].y = 7;
		}
		num = 3;

		bool beginGame = 1;

		if (restart == 1) {
			
			snake[0].x = 15;
			snake[0].y = 7;
			num = 3;
			gameOver = 0;
			beginGame = 1;
			restart = 0;
		}
		srand(time(NULL));
		RenderWindow window(VideoMode(WIDTH, HEIGHT), "Snake The Game");
		RectangleShape block;
		RectangleShape blockSnake;
		RectangleShape blockApple;

		Texture background;
		background.setRepeated(true);
		background.loadFromFile("../Textures/background.png");
		Sprite bground(background);

		Font font;
		font.loadFromFile("../Font/arial.ttf");


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

		bool checkApple = 1;

		apple.x = rand() % 30;
		apple.y = rand() % 15;

		for (int i = 0; i < 100; i++) {
			if (apple.x == snake[i].x && snake[i].y == apple.y) {
				apple.x = rand() % 30;
				apple.y = rand() % 15;
			}
		}


		apple.x = rand() % 30;
		apple.y = rand() % 15;

		Clock clock;
		float delay = 0.20;
		float chrono = 0;
		float timer_1 = 0;
		int countDeath = 15;

		while (window.isOpen())
		{

			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			chrono += time;
			timer_1 += time;


			Vector2i pos = Mouse::getPosition(window);

			Vector2i wind;
			wind.x = window.getSize().x;
			wind.y = window.getSize().y;

			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					window.close();
				}


				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (direction != 3) direction = 0;
					
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					if (direction != 2)direction = 1;
					
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					if (direction != 1)direction = 2;
					
				}
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					if (direction != 0)direction = 3;
					
				}
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					beginGame = 0;
				}
				if (Keyboard::isKeyPressed(Keyboard::R)) {
					restart = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}

				if (e.type == Event::MouseButtonPressed) {
					if (e.key.code == Mouse::Left) {
						if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
							if(beginGame == 0){
								restart = 1;
								window.close();
							}
							else {
								beginGame = 0;
							}

						}

						if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
							window.close();
						}
					}
				}



			}


			if (chrono > delay && gameOver != 1 && beginGame != 1)
			{
				chrono = 0;
				gameAction();
			}




			window.clear();
			window.draw(bground);

			for (int i = 0; i < verticalline; i++)//Прорисовка клеточек
			{
				for (int j = 0; j < horizontalline; j++)
				{
					block.setPosition(j * SIZE, i * SIZE);
					block.move(190, 50);
					window.draw(block);
				}
			}
			if (beginGame == 0) {
				for (int i = 0; i < num; i++)
				{
					blockSnake.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
					blockSnake.move(190, 50);
					if(snake[i].x < 30 && snake[i].x >= 0 && snake[i].y < 15 && snake[i].y >= 0) window.draw(blockSnake);
				}
				blockApple.setPosition(apple.x * SIZE, apple.y * SIZE);
				blockApple.move(190, 50);
				window.draw(blockApple);
			}
			RectangleShape btn_1(Vector2f(200, 65));
			btn_1.setFillColor(Color(220, 220, 220));
			FloatRect btn_1_rect = btn_1.getLocalBounds();
			btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
			btn_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));
			btn_1.setOutlineColor(Color(110, 110, 110));
			btn_1.setOutlineThickness(2);

			Text text_1("", font, 20);
			text_1.setFillColor(Color::Black);
			text_1.setStyle(Text::Bold);
			if (beginGame == 0)text_1.setString("Restart");
			else text_1.setString("Start Game");
			FloatRect text_1_rect = text_1.getLocalBounds();
			text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
			text_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));


			RectangleShape btn_2(Vector2f(200, 65));
			btn_2.setFillColor(Color(220, 220, 220));
			FloatRect btn_2_rect = btn_2.getLocalBounds();
			btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
			btn_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));
			btn_2.setOutlineColor(Color(110, 110, 110));
			btn_2.setOutlineThickness(2);

			Text text_2("", font, 20);
			text_2.setFillColor(Color::Black);
			text_2.setStyle(Text::Bold);
			text_2.setString("Exit");
			FloatRect text_2_rect = text_2.getLocalBounds();
			text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
			text_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

			if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
				btn_1.setOutlineColor(Color::Red);
			}

			if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
				btn_2.setOutlineColor(Color::Red);
			}


			window.draw(btn_1);
			window.draw(text_1);
			window.draw(btn_2);
			window.draw(text_2);

			std::string str = "To close:";

			if (gameOver == 1) {

				//Текст Game Over
				Text text("", font, 20);
				text.setFillColor(Color::Red);
				text.setStyle(Text::Bold | Text::Underlined);
				text.setString("Game Over!");
				text.setPosition(WIDTH / 2 - 80, HEIGHT / 2 - 80);

				//Текст обратного отсчёта
				Text text1("", font, 20);
				text1.setFillColor(Color::Red);
				text1.setStyle(Text::Bold | Text::Underlined);
				text1.setPosition(WIDTH / 2 - 80, (HEIGHT / 2) + 32 - 80);

				//Обратный отсчёт
				if (timer_1 > 1.0) {
					countDeath--;
					timer_1 = 0;
				}

				//Корректирока секунд обратного отсчёта в реальном времени
				str = "To close:" + std::to_string(countDeath);
				text1.setString(str);
				window.draw(text1);
				window.draw(text);

				//Завершение программы после окончания обратного отсчёта
				if (countDeath == 0) {
					window.close();
				}



			}

			window.display();
			if (restart == 1) break;
		}
	}while (restart == 1);
}