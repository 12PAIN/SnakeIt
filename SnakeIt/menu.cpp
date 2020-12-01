#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include "clTetris.h"
#include "clNewSnake.h"
#include "clSapper.h"
#include "clRaceTheGame.h"
#include "clTron.h"
#include "menu.h"
#include "clPong1.h"

using namespace sf;

void clMenu::menu(int WIDTH, int HEIGHT) {

	//������ ����
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SnakeIt!");


	Image icon;
	icon.loadFromFile("../Textures/icon.png");
	
	window.setIcon(100, 100, icon.getPixelsPtr());

	//�������� ������
	Font font;
	font.loadFromFile("../Font/Arial.ttf");
	
	//�������� �������� ������
	Texture btn_tex;
	btn_tex.loadFromFile("../Textures/button.png");

	//�������� �������� ����
	Texture bground;
	bground.loadFromFile("../Textures/background.png");
	Sprite background(bground);

	//���������� ��� �������� ������ ����
	bool menu_dropdown = 0;

	while (window.isOpen()) {

		//��������� ������� ����
		Vector2i pos = Mouse::getPosition(window);

		//��������� �������
		Event e;

		Vector2i wind;
		wind.x = window.getSize().x;
		wind.y = window.getSize().y;

		while (window.pollEvent(e)) {

			if (e.type == Event::Closed) {
				window.close();
			}



			//�������� ������ �� ������
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

						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 5.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 5.5 + wind.y / 22.15))) {
							NewSnake snake;
							snake.Snake();
						}

						if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.5 + wind.y / 22.15))) {
							RGame race;
							race.RaceTheGame();
						}

						
						if ((pos.x >= (wind.x / 3.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 3.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
							clTron tron;
							tron.TronGame();
						}

						if ((pos.x >= (wind.x / 1.5 - wind.x / 12.8)) && (pos.x <= (wind.x / 1.5 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
							clPong pong;
							pong.Pong();
						}

					}
				}
			}




		}

		window.draw(background);

		if (menu_dropdown != 1) {
			Sprite btn_1(btn_tex);
			FloatRect btn_1_rect = btn_1.getLocalBounds();
			btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
			btn_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));
			

			Text text_1("", font, 20);
			text_1.setFillColor(Color::Black);
			text_1.setStyle(Text::Bold);
			text_1.setString("New game");
			FloatRect text_1_rect = text_1.getLocalBounds();
			text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
			text_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));


			Sprite btn_2(btn_tex);
			FloatRect btn_2_rect = btn_2.getLocalBounds();
			btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
			btn_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.5f));

			Text text_2("", font, 20);
			text_2.setFillColor(Color::Black);
			text_2.setStyle(Text::Bold);
			text_2.setString("Exit");
			FloatRect text_2_rect = text_2.getLocalBounds();
			text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
			text_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.5f));

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.5 + wind.y / 22.15))) {
				btn_2.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
				btn_1.setColor(Color(255, 255, 255, 200));
			}

			window.draw(btn_1);
			window.draw(text_1);
			window.draw(btn_2);
			window.draw(text_2);
			

		}
		else {
			Sprite btn_1(btn_tex);
			FloatRect btn_1_rect = btn_1.getLocalBounds();
			btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
			btn_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));
			

			Text text_1("", font, 20);
			text_1.setFillColor(Color::Black);
			text_1.setStyle(Text::Bold);
			text_1.setString("Tetris");
			FloatRect text_1_rect = text_1.getLocalBounds();
			text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
			text_1.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 3.0f));


			Sprite btn_7(btn_tex);
			FloatRect btn_7_rect = btn_7.getLocalBounds();
			btn_7.setOrigin(btn_7_rect.left + btn_7_rect.width / 2.0f, btn_7_rect.top + btn_7_rect.height / 2.0f);
			btn_7.setPosition(Vector2f(WIDTH / 1.5f, HEIGHT / 3.0f));


			Text text_7("", font, 20);
			text_7.setFillColor(Color::Black);
			text_7.setStyle(Text::Bold);
			text_7.setString("The Pong");
			FloatRect text_7_rect = text_7.getLocalBounds();
			text_7.setOrigin(text_7_rect.left + text_7_rect.width / 2.0f, text_7_rect.top + text_7_rect.height / 2.0f);
			text_7.setPosition(Vector2f(WIDTH / 1.5f, HEIGHT / 3.0f));

			Sprite btn_6(btn_tex);
			FloatRect btn_6_rect = btn_6.getLocalBounds();
			btn_6.setOrigin(btn_6_rect.left + btn_6_rect.width / 2.0f, btn_6_rect.top + btn_6_rect.height / 2.0f);
			btn_6.setPosition(Vector2f(WIDTH / 3.0f, HEIGHT / 3.0f));


			Text text_6("", font, 20);
			text_6.setFillColor(Color::Black);
			text_6.setStyle(Text::Bold);
			text_6.setString("Tron Game");
			FloatRect text_6_rect = text_6.getLocalBounds();
			text_6.setOrigin(text_6_rect.left + text_6_rect.width / 2.0f, text_6_rect.top + text_6_rect.height / 2.0f);
			text_6.setPosition(Vector2f(WIDTH / 3.0f, HEIGHT / 3.0f));


			Sprite btn_4(btn_tex);
			
			FloatRect btn_4_rect = btn_4.getLocalBounds();
			btn_4.setOrigin(btn_4_rect.left + btn_4_rect.width / 2.0f, btn_4_rect.top + btn_4_rect.height / 2.0f);
			btn_4.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 5.5f));


			Text text_4("", font, 20);
			text_4.setFillColor(Color::Black);
			text_4.setStyle(Text::Bold);
			text_4.setString("Snake The Game");
			FloatRect text_4_rect = text_4.getLocalBounds();
			text_4.setOrigin(text_4_rect.left + text_4_rect.width / 2.0f, text_4_rect.top + text_4_rect.height / 2.0f);
			text_4.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 5.5f));

			Sprite btn_5(btn_tex);
			FloatRect btn_5_rect = btn_5.getLocalBounds();
			btn_5.setOrigin(btn_5_rect.left + btn_5_rect.width / 2.0f, btn_5_rect.top + btn_5_rect.height / 2.0f);
			btn_5.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.5f));

			Text text_5("", font, 20);
			text_5.setFillColor(Color::Black);
			text_5.setStyle(Text::Bold);
			text_5.setString("Race Game");
			FloatRect text_5_rect = text_5.getLocalBounds();
			text_5.setOrigin(text_5_rect.left + text_5_rect.width / 2.0f, text_5_rect.top + text_5_rect.height / 2.0f);
			text_5.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.5f));

			Sprite btn_3(btn_tex);
			FloatRect btn_3_rect = btn_3.getLocalBounds();
			btn_3.setOrigin(btn_3_rect.left + btn_3_rect.width / 2.0f, btn_3_rect.top + btn_3_rect.height / 2.0f);
			btn_3.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));

			Text text_3("", font, 20);
			text_3.setFillColor(Color::Black);
			text_3.setStyle(Text::Bold);
			text_3.setString("Sapper");
			FloatRect text_3_rect = text_1.getLocalBounds();
			text_3.setOrigin(text_3_rect.left + text_3_rect.width / 2.0f, text_3_rect.top + text_3_rect.height / 2.0f);
			text_3.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));


			Sprite btn_2(btn_tex);
			FloatRect btn_2_rect = btn_2.getLocalBounds();
			btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
			btn_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.2f));

			Text text_2("", font, 20);
			text_2.setFillColor(Color::Black);
			text_2.setStyle(Text::Bold);
			text_2.setString("Return");
			FloatRect text_2_rect = text_2.getLocalBounds();
			text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
			text_2.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 1.2f));
			

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.2 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.2 + wind.y / 22.15))) {
				btn_2.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
				btn_1.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 2. - wind.y / 22.15)) && (pos.y <= (wind.y / 2. + wind.y / 22.15))) {
				btn_3.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 5.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 5.5 + wind.y / 22.15))) {
				btn_4.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 2.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 2.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 1.5 - wind.y / 22.15)) && (pos.y <= (wind.y / 1.5 + wind.y / 22.15))) {
				btn_5.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 3.0 - wind.x / 12.8)) && (pos.x <= (wind.x / 3.0 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
				btn_6.setColor(Color(255, 255, 255, 200));
			}

			if ((pos.x >= (wind.x / 1.5 - wind.x / 12.8)) && (pos.x <= (wind.x / 1.5 + wind.x / 12.8)) && (pos.y >= (wind.y / 3. - wind.y / 22.15)) && (pos.y <= (wind.y / 3. + wind.y / 22.15))) {
				btn_7.setColor(Color(255, 255, 255, 200));
			}


			window.draw(btn_1);
			window.draw(text_1);
			window.draw(btn_2);
			window.draw(text_2);
			window.draw(btn_3);
			window.draw(text_3);
			window.draw(btn_4);
			window.draw(text_4);
			window.draw(btn_5);
			window.draw(text_5);
			window.draw(btn_6);
			window.draw(text_6);
			window.draw(btn_7);
			window.draw(text_7);
			

		}
		

		window.display();
	}


};
