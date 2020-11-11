#include "clSapper.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>

using namespace sf;

void clSapper::Sapper(int WEIGHT, int HEIGHT, bool* restart){
        
        //��������� �������
        srand(time(0));

        //�������� ����
        Texture background;
        background.setRepeated(true);
        background.loadFromFile("../Textures/background.png");
        Sprite bground(background);

        RenderWindow window(VideoMode(WEIGHT, HEIGHT), "Sapper");

        //��������
        Texture texture;
        texture.loadFromFile("../Textures/sapper.png");
        Sprite s(texture);

        //�����
        Font font;
        font.loadFromFile("../Font/arial.ttf");

        //������
        Clock clock;
        float timer = 0;


        //���������� ����� ����������� ����������� �����
        for (int i = 1; i <= 10; i++){
            for (int j = 1; j <= 10; j++){
                gridView[i][j] = 10;
            }
        }

        //���������� ����
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                if (rand() % 5 == 0) {
                    gridLogic[i][j] = 9;
                    bombs++;
                }
                else gridLogic[i][j] = 0;

            }
        }

        //���������� ���� ����������� ����
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                if (gridLogic[i][j] != 9) {
                    if (gridLogic[i - 1][j - 1] == 9) gridLogic[i][j]++;
                    if (gridLogic[i - 1][j] == 9) gridLogic[i][j]++;
                    if (gridLogic[i - 1][j + 1] == 9) gridLogic[i][j]++;
                    if (gridLogic[i][j - 1] == 9) gridLogic[i][j]++;
                    if (gridLogic[i][j + 1] == 9) gridLogic[i][j]++;
                    if (gridLogic[i + 1][j - 1] == 9) gridLogic[i][j]++;
                    if (gridLogic[i + 1][j] == 9) gridLogic[i][j]++;
                    if (gridLogic[i + 1][j + 1] == 9) gridLogic[i][j]++;
                }
                else {
                    continue;
                }
            }
        }

        //�������� ��������� ������
        int countDeath = 15;

        //������ ��� ��������� � ������ ��������� �������
        std::string str;

        //���������� ����� �� ��������� ������� ������ ���
        bool gameOvervar = 0;
        bool winVar = 0;

        while (window.isOpen()) {

            //������ �������� �������
            gameOvervar = gameOver();
            winVar = win();

            //��������� �������
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            //��������� ��������� ����
            Vector2i pos = Mouse::getPosition(window);

            //��������� ��� ��������� ���� �� ���������
            int x = (pos.x -416)/ w;
            int y = (pos.y -160)/ w;


            //��������� �������
            Event event;

            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == Keyboard::R) {
                        *restart = 1;
                        window.close();
                    }
                }

                if (event.type == Event::MouseButtonPressed && gameOvervar != 1 && winVar != 1) {
                    if (event.key.code == Mouse::Left) {

                        //����� �� ������?
                        if (gridView[x][y] != 11) {
                            gridView[x][y] = gridLogic[x][y];
                            cubeIsOpen[x][y] = 1;
                        }
                    }
                    if (event.key.code == Mouse::Right) {

                        //��������� ��� ������ ������
                        if(gridView[x][y] == 10) gridView[x][y] = 11;
                        else if(gridView[x][y] == 11) gridView[x][y] = 10;

                        
                    }

                }

            }


            //�������� ���� ������ ������ ��� ������� �� ���� �� ���������
            for (int i = 1; i <= 10; i++) {
                for (int j = 1; j <= 10; j++) {
                    if (gridView[i][j] == 0 && cubeIsOpen[i][j] == 1) {
                        if (gridLogic[i - 1][j - 1] == 0) {
                            gridView[i - 1][j - 1] = 0;
                            cubeIsOpen[i - 1][j - 1] = 1;
                        }

                        if (gridLogic[i - 1][j] == 0) {
                            gridView[i - 1][j] = 0;
                            cubeIsOpen[i - 1][j] = 1;
                        }

                        if (gridLogic[i - 1][j + 1] == 0) {
                            gridView[i - 1][j + 1] = 0;
                            cubeIsOpen[i - 1][j + 1] = 1;
                        }


                        if (gridLogic[i][j - 1] == 0) {
                            gridView[i][j - 1] = 0;
                            cubeIsOpen[i][j - 1] = 1;
                        }

                        if (gridLogic[i][j + 1] == 0) {
                            gridView[i][j + 1] = 0;
                            cubeIsOpen[i][j + 1] = 1;
                        }


                        if (gridLogic[i + 1][j - 1] == 0) {
                            gridView[i + 1][j - 1] = 0;
                            cubeIsOpen[i + 1][j - 1] = 1;
                        }


                        if (gridLogic[i + 1][j] == 0) {
                            gridView[i + 1][j] = 0;
                            cubeIsOpen[i + 1][j] = 1;
                        }

                        if (gridLogic[i + 1][j + 1] == 0) {
                            gridView[i + 1][j + 1] = 0;
                            cubeIsOpen[i + 1][j + 1] = 1;
                        }
                    }
                }
            }


            //      !���������!
            window.clear(Color::White);

            window.draw(bground);

            //����������� ����
            for (int i = 1; i <= 10; i++) {
                for (int j = 1; j <= 10; j++) {
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
                    s.setPosition(i * w, j * w);
                    s.move(416, 160);
                    window.draw(s);
                }
            }

            
            //����� ���� ��������
            if (gameOvervar == 1) {

                //����� Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Red);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("Game Over!");
                text.setOutlineColor(Color::Black);
                text.setOutlineThickness(2);
                text.setPosition(WEIGHT / 2, HEIGHT / 2);

                //����� ��������� �������
                Text text1("", font, 20);
                text1.setFillColor(Color::Red);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setOutlineColor(Color::Black);
                text1.setOutlineThickness(2);
                text1.setPosition(WEIGHT / 2, (HEIGHT / 2) + 32);

                //�������� ������
                if (timer > 1.0) {
                    countDeath--;
                    timer = 0;
                }

                //������������ ������ ��������� ������� � �������� �������
                str = "To close:" + std::to_string(countDeath);
                text1.setString(str);
                window.draw(text1);
                window.draw(text);

                //���������� ��������� ����� ��������� ��������� �������
                if (countDeath == 0) {
                    window.close();
                }



            }

            //����� ���� �������
            if (gameOvervar != 1 && winVar == 1) {

                //����� Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Green);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("You Win!");
                text.setOutlineColor(Color::Black);
                text.setOutlineThickness(2);
                text.setPosition(WEIGHT / 2, HEIGHT / 2);

                //����� ��������� �������
                Text text1("", font, 20);
                text1.setFillColor(Color::Green);
                text1.setOutlineColor(Color::Black);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setOutlineThickness(2);
                text1.setPosition(WEIGHT / 2, (HEIGHT / 2) + 32);

                //�������� ������
                if (timer > 1.0) {
                    countDeath--;
                    timer = 0;
                }

                //������������ ������ ��������� ������� � �������� �������
                str = "To close:" + std::to_string(countDeath);
                text1.setString(str);
                window.draw(text1);
                window.draw(text);

                //���������� ��������� ����� ��������� ��������� �������
                if (countDeath == 0) {
                    window.close();
                }



            }

            //�������������� ������
            Text text2("", font, 20);
            text2.setFillColor(Color::Black);
            text2.setStyle(Text::Bold | Text::Italic);
            text2.setString("To exit press ESC");
            text2.setPosition(350 + 5*w, 110);
            window.draw(text2);

            Text text3("", font, 20);
            text3.setFillColor(Color::Black);
            text3.setStyle(Text::Bold | Text::Italic);
            text3.setString("To restart press R");
            text3.setPosition(350 + 5 * w , 145);
            window.draw(text3);

            window.display();
        }

    };

//������� �������� ���������
bool clSapper::gameOver() {
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (cubeIsOpen[i][j] == 1 && gridLogic[i][j] == 9) return 1;
    return 0;
};

//������� �������� ��������(����� �� ���� ������ ����� ������ ������
bool clSapper::win() {
    int count = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (gridView[i][j] == 11 && gridLogic[i][j] == 9) count++;

    if (count == bombs) return 1;

    return 0;
};





