#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include "clTetris.h"
#include "clSapper.h"
#include "menu.h"

using namespace sf;

void clMenu::menu(int WIDTH, int HEIGHT) {

	//Рендер окна
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SnakeIt!");

	//загрузка шрифта
	Font font;
	font.loadFromFile("../Font/Arial.ttf");
	
	//Загрузка текстуры фона
	Texture bground;
	bground.loadFromFile("../Textures/background.png");
	Sprite background(bground);

	//Переменная для открытия пункта меню
	bool menu_dropdown = 0;

	while (window.isOpen()) {

		//Получение позиции мыши
		Vector2i pos = Mouse::getPosition(window);

		//Обработка событий
		Event e;

		Vector2i wind;
		wind.x = window.getSize().x;
		wind.y = window.getSize().y;

		while (window.pollEvent(e)) {

			if (e.type == Event::Closed) {
				window.close();
			}



			//Проверка нажата ли кнопка
			if (menu_dropdown != 1) {
				if (e.type == Event::MouseButtonPressed) {
					if (e.key.code == Mouse::Left) {
						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.5 + wind.y / 22.15))) {
							window.close();
						}

						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
							menu_dropdown = 1;
						}
					}
				}
			}
			else {
				if (e.type == Event::MouseButtonPressed) {
					if (e.key.code == Mouse::Left) {
						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.2 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.2 + wind.y / 22.15))) {
							menu_dropdown = 0;
						}

						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
							clTetris tetris;
							tetris.Tetris(WIDTH, HEIGHT);
						}

						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 2. - wind.y / 22.15)) && (pos.y <= (wind.y / 2. + wind.y / 22.15))) {
							clSapper sapper;
							sapper.Sapper(WIDTH, HEIGHT);
						}

						


					}
				}
			}




		}

		window.draw(background);

		if (menu_dropdown != 1) {
			RectangleShape btn_1(Vector2f(200, 65));
			btn_1.setFillColor(Color(220, 220, 220));
			FloatRect btn_1_rect = btn_1.getLocalBounds();
			btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
			btn_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));
			btn_1.setOutlineColor(Color(110, 110, 110));
			btn_1.setOutlineThickness(2);

			Text text_1("", font, 20);
			text_1.setFillColor(Color::Black);
			text_1.setStyle(Text::Bold);
			text_1.setString("New game");
			FloatRect text_1_rect = text_1.getLocalBounds();
			text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
			text_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));


			RectangleShape btn_2(Vector2f(200, 65));
			btn_2.setFillColor(Color(220, 220, 220));
			FloatRect btn_2_rect = btn_2.getLocalBounds();
			btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
			btn_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.5f));
			btn_2.setOutlineColor(Color(110, 110, 110));
			btn_2.setOutlineThickness(2);

			Text text_2("", font, 20);
			text_2.setFillColor(Color::Black);
			text_2.setStyle(Text::Bold);
			text_2.setString("Exit");
			FloatRect text_2_rect = text_2.getLocalBounds();
			text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
			text_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.5f));

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.5 + wind.y / 22.15))) {
				btn_2.setOutlineColor(Color::Red);
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
				btn_1.setOutlineColor(Color::Red);
			}

			window.draw(btn_1);
			window.draw(text_1);
			window.draw(btn_2);
			window.draw(text_2);
			

		}
		else {
			RectangleShape btn_1(Vector2f(200, 65));
			btn_1.setFillColor(Color(220, 220, 220));
			FloatRect btn_1_rect = btn_1.getLocalBounds();
			btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
			btn_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));
			btn_1.setOutlineColor(Color(110, 110, 110));
			btn_1.setOutlineThickness(2);

			Text text_1("", font, 20);
			text_1.setFillColor(Color::Black);
			text_1.setStyle(Text::Bold);
			text_1.setString("Tetris");
			FloatRect text_1_rect = text_1.getLocalBounds();
			text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
			text_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));

			RectangleShape btn_3(Vector2f(200, 65));
			btn_3.setFillColor(Color(220, 220, 220));
			FloatRect btn_3_rect = btn_3.getLocalBounds();
			btn_3.setOrigin(btn_3_rect.left + btn_3_rect.width / 2.0f, btn_3_rect.top + btn_3_rect.height / 2.0f);
			btn_3.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));
			btn_3.setOutlineColor(Color(110, 110, 110));
			btn_3.setOutlineThickness(2);

			Text text_3("", font, 20);
			text_3.setFillColor(Color::Black);
			text_3.setStyle(Text::Bold);
			text_3.setString("Sapper");
			FloatRect text_3_rect = text_1.getLocalBounds();
			text_3.setOrigin(text_3_rect.left + text_3_rect.width / 2.0f, text_3_rect.top + text_3_rect.height / 2.0f);
			text_3.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));


			RectangleShape btn_2(Vector2f(200, 65));
			btn_2.setFillColor(Color(220, 220, 220));
			FloatRect btn_2_rect = btn_2.getLocalBounds();
			btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
			btn_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.2f));
			btn_2.setOutlineColor(Color(110, 110, 110));
			btn_2.setOutlineThickness(2);

			Text text_2("", font, 20);
			text_2.setFillColor(Color::Black);
			text_2.setStyle(Text::Bold);
			text_2.setString("Return");
			FloatRect text_2_rect = text_2.getLocalBounds();
			text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
			text_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.2f));


			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.2 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.2 + wind.y / 22.15))) {
				btn_2.setOutlineColor(Color::Red);
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
				btn_1.setOutlineColor(Color::Red);
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 2. - wind.y / 22.15)) && (pos.y <= (wind.y / 2. + wind.y / 22.15))) {
				btn_3.setOutlineColor(Color::Red);
			}



			window.draw(btn_1);
			window.draw(text_1);
			window.draw(btn_2);
			window.draw(text_2);
			window.draw(btn_3);
			window.draw(text_3);

		}
		

		window.display();
	}


};
