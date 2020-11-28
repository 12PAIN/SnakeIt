#include "clSapper.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>

using namespace sf;

void clSapper::Sapper(int WIDTH, int HEIGHT){
        
    bool restart = 0;

    do {

        if (restart == 1) {
            restart = 0;
        }

        //Установка рандома
        srand(time(0));

        //Загрузка фона
        Texture background;
        background.setRepeated(true);
        background.loadFromFile("../Textures/background.png");
        Sprite bground(background);

        RenderWindow window(VideoMode(WIDTH, HEIGHT), "SnakeIt:Sapper");

        //Текстура
        Texture texture;
        texture.loadFromFile("../Textures/sapper.png");
        Sprite s(texture);


        //Загрузка текстуры кнопки
        Texture btn_tex;
        btn_tex.loadFromFile("../Textures/button.png");

        //Шрифт
        Font font;
        font.loadFromFile("../Font/arial.ttf");

        //таймер
        Clock clock;
        float timer = 0;



        //Заполнение сетки отображения изначальным полем
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                gridView[i][j] = 10;
                cubeIsOpen[i][j] = 0;
            }
        }

        //Заполнение бомб
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                if (rand() % 5 == 0) {
                    gridLogic[i][j] = 9;
                    bombs++;
                }
                else gridLogic[i][j] = 0;

            }
        }

        //Заполнение поля количеством бомб
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

        //Счёткчик обратного отсчёт
        int countDeath = 15;

        //Строка для изменения в строке обратного отсчёта
        std::string str;

        //Переменные чтобы не запускать функцию каждый раз
        bool gameOvervar = 0;
        bool winVar = 0;

        while (window.isOpen()) {

            //Запись значений функций
            gameOvervar = gameOver();
            winVar = win();

            //Настройка таймера
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;




            //Обработка событий
            Event event;

            //Получение размера окна
            Vector2i wind;
            wind.x = window.getSize().x;
            wind.y = window.getSize().y;

            //Получение координат мыши
            Vector2i pos = Mouse::getPosition(window);

            //Обработка для программы этих же координат
            int x = (pos.x - wind.x / 3.0769) / (wind.x / 40);
            int y = (pos.y - wind.y / 4.5) / (wind.y / 22.5);



            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == Keyboard::R) {
                        restart = 1;
                        window.close();
                    }
                }

                if (event.type == Event::MouseButtonPressed) {
                    if (event.key.code == Mouse::Left && gameOvervar != 1 && winVar != 1) {

                        //стоит ли флажок?
                        if (gridView[x][y] != 11) {
                            gridView[x][y] = gridLogic[x][y];
                            cubeIsOpen[x][y] = 1;
                        }

                    }

                    if (event.key.code == Mouse::Left) {

                        if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                            restart = 1;

                        }

                        if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                            window.close();
                        }
                    }

                    if (event.key.code == Mouse::Right && gameOvervar != 1 && winVar != 1 ) {

                        //Установка или снятие флажка
                        if (gridView[x][y] == 10) gridView[x][y] = 11;
                        else if (gridView[x][y] == 11) gridView[x][y] = 10;


                    }

                }

            }



            //Открытие всех пустых клеток при нажатии на одну из множества
            for (int i = 1; i <= 10; i++) {
                for (int j = 1; j <= 10; j++) {
                    if (gridView[i][j] == 0 && cubeIsOpen[i][j] == 1) {
                        if (gridLogic[i - 1][j - 1] != 9) {
                            gridView[i - 1][j - 1] = gridLogic[i - 1][j - 1];
                            cubeIsOpen[i - 1][j - 1] = 1;
                        }

                        if (gridLogic[i - 1][j] != 9) {
                            gridView[i - 1][j] = gridLogic[i - 1][j];
                            cubeIsOpen[i - 1][j] = 1;
                        }

                        if (gridLogic[i - 1][j + 1] != 9) {
                            gridView[i - 1][j + 1] = gridLogic[i - 1][j + 1];
                            cubeIsOpen[i - 1][j + 1] = 1;
                        }


                        if (gridLogic[i][j - 1] != 9) {
                            gridView[i][j - 1] = gridLogic[i][j - 1];
                            cubeIsOpen[i][j - 1] = 1;
                        }

                        if (gridLogic[i][j + 1] != 9) {
                            gridView[i][j + 1] = gridLogic[i][j + 1];
                            cubeIsOpen[i][j + 1] = 1;
                        }


                        if (gridLogic[i + 1][j - 1] != 9) {
                            gridView[i + 1][j - 1] = gridLogic[i + 1][j - 1];
                            cubeIsOpen[i + 1][j - 1] = 1;
                        }


                        if (gridLogic[i + 1][j] != 9) {
                            gridView[i + 1][j] = gridLogic[i + 1][j];
                            cubeIsOpen[i + 1][j] = 1;
                        }

                        if (gridLogic[i + 1][j + 1] != 9) {
                            gridView[i + 1][j + 1] = gridLogic[i + 1][j + 1];
                            cubeIsOpen[i + 1][j + 1] = 1;
                        }
                    }
                }
            }






            //      !Отрисовка!
            window.clear(Color::White);

            window.draw(bground);

            //Отображение поля
            for (int i = 1; i <= 10; i++) {
                for (int j = 1; j <= 10; j++) {
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
                    s.setPosition(i * w, j * w);
                    s.move(416, 160);
                    window.draw(s);
                }
            }


            //Текст если проиграл
            if (gameOvervar == 1) {

                //Текст Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Red);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("Game Over!");
                text.setOutlineColor(Color::Black);
                FloatRect text_rect = text.getLocalBounds();
                text.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
                text.setOutlineThickness(2);
                text.setPosition(WIDTH / 2, HEIGHT / 2);

                //Текст обратного отсчёта
                Text text1("", font, 20);
                text1.setFillColor(Color::Red);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setOutlineColor(Color::Black);
                text1.setOutlineThickness(2);


                //Обратный отсчёт
                if (timer > 1.0) {
                    countDeath--;
                    timer = 0;
                }

                //Корректирока секунд обратного отсчёта в реальном времени
                str = "To close:" + std::to_string(countDeath);
                text1.setString(str);
                FloatRect text1_rect = text1.getLocalBounds();
                text1.setOrigin(text1_rect.left + text1_rect.width / 2.0f, text1_rect.top + text1_rect.height / 2.0f);
                text1.setPosition(WIDTH / 2, (HEIGHT / 2) + 32);

                window.draw(text1);
                window.draw(text);

                //Завершение программы после окончания обратного отсчёта
                if (countDeath == 0) {
                    window.close();
                }



            }

            //Текст если выйграл
            if (gameOvervar != 1 && winVar == 1) {

                //Текст Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Green);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("You Win!");
                FloatRect text_rect = text.getLocalBounds();
                text.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
                text.setOutlineColor(Color::Black);
                text.setOutlineThickness(2);
                text.setPosition(WIDTH / 2, HEIGHT / 2);

                //Текст обратного отсчёта
                Text text1("", font, 20);
                text1.setFillColor(Color::Green);
                text1.setOutlineColor(Color::Black);
                FloatRect text1_rect = text1.getLocalBounds();
                text1.setOrigin(text1_rect.left + text1_rect.width / 2.0f, text1_rect.top + text1_rect.height / 2.0f);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setOutlineThickness(2);
                text1.setPosition(WIDTH / 2, (HEIGHT / 2) + 32);

                //Обратный отсчёт
                if (timer > 1.0) {
                    countDeath--;
                    timer = 0;
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


            //Кнопки
            Sprite btn_1(btn_tex);
            FloatRect btn_1_rect = btn_1.getLocalBounds();
            btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
            btn_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            Text text_1("", font, 20);
            text_1.setFillColor(Color::Black);
            text_1.setStyle(Text::Bold);
            text_1.setString("Restart");
            FloatRect text_1_rect = text_1.getLocalBounds();
            text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
            text_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));


            Sprite btn_2(btn_tex);
            FloatRect btn_2_rect = btn_2.getLocalBounds();
            btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
            btn_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            Text text_2("", font, 20);
            text_2.setFillColor(Color::Black);
            text_2.setStyle(Text::Bold);
            text_2.setString("Exit");
            FloatRect text_2_rect = text_2.getLocalBounds();
            text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
            text_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                btn_1.setColor(Color(255, 255, 255, 200));
            }

            if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                btn_2.setColor(Color(255, 255, 255, 200));
            }


            window.draw(btn_1);
            window.draw(text_1);
            window.draw(btn_2);
            window.draw(text_2);

            window.display();

            if (restart == 1) {
                break;
            }

        }
    }while (restart == 1);
        

    };

//Функция проверки проигрыща
bool clSapper::gameOver() {
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (cubeIsOpen[i][j] == 1 && gridLogic[i][j] == 9) return 1;
    return 0;
};

//Функция проверки выйгрыша(Когда на всех бомбах будут стоять флажки
bool clSapper::win() {
    int count = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (gridView[i][j] == 11 && gridLogic[i][j] == 9) count++;

    if (count == bombs) return 1;

    return 0;
};





