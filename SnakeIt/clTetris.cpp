#include "clTetris.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <SFML/Audio.hpp>

using namespace sf;

void clTetris::Tetris(int WIDTH, int HEIGHT) {

    //Инициализация переменной рестарта
    bool restart = 0;
    
    do{
        

        //Очистка поля
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                field[i][j] = 0;
            }
        }
    
        //Установка рандома
        srand(time(0));

        SoundBuffer buffer;
        buffer.loadFromFile("../Audio/test1.wav");

        Sound sound;
        sound.setBuffer(buffer);
    
        RenderWindow window(VideoMode(WIDTH, HEIGHT), "SnakeIt:Tetris");
    
        //Загрузка "сетки"
        Texture net_tex;
        net_tex.loadFromFile("../Textures/net.png");
        Sprite net(net_tex);
        net.setTextureRect(IntRect(0, 0, 18, 18));
    
        //Загрузка фона
        Texture background;
        background.setRepeated(true);
        background.loadFromFile("../Textures/background_tetris.png");
        Sprite bground(background);

        Image icon;
        icon.loadFromFile("../Textures/icon_tetris.png");
        window.setIcon(100, 100, icon.getPixelsPtr());

        //Загрузка текстуры кнопки
        Texture btn_tex;
        btn_tex.loadFromFile("../Textures/button.png");
    
        //Загрузка рамки
        Texture frame_tex;
        frame_tex.loadFromFile("../Textures/frame.png");
        Sprite frame(frame_tex);
        frame.setTextureRect(IntRect(0, 0, 200, 380));
    
        //Шрифт
        Font font;
        font.loadFromFile("../Font/arial.ttf");
    
        //Загрузка текстуры кубиков
        Texture tex1;
        tex1.setRepeated(true);
        tex1.loadFromFile("../Textures/tex2.png");
    
        //Спрайт кубиков
        Sprite sprite(tex1);
        sprite.setTextureRect(IntRect(0, 0, 18, 18));
    
        //Инициализация для таймера
        Clock clock;
        float timer = 0, delay = 0.3, timer_1 = 0;
    
    
        //Тип фигуры
        int n = rand() % 7;
        int n_new = n;
        int colorNum = 0;
        int colorNum_new = 0;
        
        for (int i = 0; i < 7; i++) {
            if (n == i) {
                colorNum = i + 1;
            }
        }

        for (int i = 0; i < 7; i++) {
            if (n_new == i) {
                colorNum_new = i + 1;
            }
        }

        


    
        //Движение по горизонтали
        int dx = 0;

        float dy = 0.3;
    
        //Поворот
        bool rotate = 0;
    
        //Игра только запустилась?
        bool beginGame = true;
    
        //Счётчик таймера для проигрыша/Обратный отсчёт
        int countDeath = 15;
    
        //Счёт игрока
        struct playerScore {
            std::string str;
            int num = 0;
        };
        playerScore score;

        //Обнуление рестарта
        restart = 0;
        beginGame_1 = 1;
    
        while (window.isOpen()) {
    
            //Первоначальная настройка таймеров. timer_1 нужен для обратного отсчёта. timer - для счёта когда спускаться вниз
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            timer_1 += time;
    
            
            Vector2i pos = Mouse::getPosition(window);

            Vector2i wind;
            wind.x = window.getSize().x;
            wind.y = window.getSize().y;
    
    
            //Обработка произошедших событий
            Event event;
            while (window.pollEvent(event)) {
    
                if (event.type == Event::Closed) window.close();
    
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up) {
                        rotate = true;
                    }
                    if (event.key.code == Keyboard::Left) {
                        dx = -1;
                    }
                    if (event.key.code == Keyboard::Right) {
                        dx = 1;
                    }
                    if (event.key.code == Keyboard::Down) {
                        delay = 0.03;
                    }
                    if (event.key.code == Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == Keyboard::R) {
                        restart = 1;
                        window.close();
                    }
                    if (event.key.code == Keyboard::S) {
                        beginGame_1 = 0;
                    }
    
                }

                if (event.type == Event::MouseButtonPressed) {
                    if(event.key.code == Mouse::Left){
                        if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                            if (beginGame_1 != 1) {
                                restart = 1;
                                window.close();
                            }
                            else {
                                beginGame_1 = 0;
                            }
                        }

                        if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                            window.close();
                        }
                    }
                }

            }
            
            
            //Проверка не проиграна ли игра, чтобы новые кубики не создавались
            if (!gameOver()){

                if (beginGame) {

                    beginGame = false;

                    n = n_new;

                    for (int i = 0; i < 7; i++) {
                        if (n == i) {
                            colorNum = i + 1;
                        }
                    }

                    for (int i = 0; i < 4; i++) {
                        a[i].x = figures[n][i] % 2 + 4;

                        a[i].y = figures[n][i] / 2;
                    }

                    n_new = rand() % 7;

                    for (int i = 0; i < 7; i++) {
                        if (n_new == i) {
                            colorNum_new = i + 1;
                        }
                    }

                }
    
                // Движение по горизонтали с проверкой выхода за границы
                if (beginGame_1 != 1) {
                    for (int i = 0; i < 4; i++) {
                        b[i] = a[i];
                        a[i].x += dx;
                    }

                    if (!check())
                        for (int i = 0; i < 4; i++) {
                            a[i] = b[i];
                        }
                }
    
                //Поворот с проверкой выхода за границы
                if (rotate && beginGame_1 != 1) {
                    Point p = a[1];
                    for (int i = 0; i < 4; i++) {
                        b[i] = a[i];
                        int x = a[i].y - p.y;
                        int y = a[i].x - p.x;
                        a[i].x = p.x - x;
                        a[i].y = p.y + y;
                    }
    
                    if (!check())
                        for (int i = 0; i < 4; i++) {
                            a[i] = b[i];
                        }
    
    
                }
    
                // Движение вниз и создание новых кубиков
                if (timer > delay && beginGame_1 != 1) {
                    for (int i = 0; i < 4; i++) {
                        b[i] = a[i];
                        a[i].y++;
                    }
    
                    if (!check()) {
    
                        for (int i = 0; i < 4; i++) {
                            field[b[i].y][b[i].x] = colorNum;
                            sound.play();
                        }
    
                        n = n_new;

                        for (int i = 0; i < 7; i++) {
                            if (n == i) {
                                colorNum = i + 1;
                            }
                        }

                        for (int i = 0; i < 4; i++) {
                            a[i].x = figures[n][i] % 2 + 4;
                            a[i].y = figures[n][i] / 2;
                        }
                        n_new = rand() % 7;
                        for (int i = 0; i < 7; i++) {
                            if (n_new == i) {
                                colorNum_new = i + 1;
                            }
                        }
    
                    }
    
                    timer = 0;
                }

                if(score.num < 2000)
                    dy = 0.3 - 0.025*(score.num / 500);
                if(score.num >= 2000)
                    dy = 0.22 - 0.015 * (score.num / 1000);

                //Создание первых кубиков
                
                
    
                //Обнуление используемых значений
                dx = 0;
                rotate = 0;
                delay = dy;
    

                //для записи строк для проверки какие строки убраны
                int strCheck = 0;

                //Проверка и убирание целой полосы 
                int k = M - 1;
                for (int i = M - 1; i > 0; i--)
                {
                    int count = 0;
                    for (int j = 0; j < N; j++)
                    {
                        if (field[i][j]) count++;
                        field[k][j] = field[i][j];
                    }
                    if (count < N) { k--; }
                    else {
                        
                        strCheck++;
                    
                    }
                }
                if (strCheck == 4) {
                    score.num += 1000;
                }
                else if (strCheck == 3) {
                    score.num += 600;
                }
                else if (strCheck == 2) {
                    score.num += 300;
                }
                else if (strCheck == 1) {
                    score.num += 100;
                }

                strCheck = 0;
            }

            


    
            window.clear(Color::White);
    
    
    
            //Отрисовка фона
            window.draw(bground);
    
            //Отрисовка рамки
            frame.setPosition(35, 80);
            window.draw(frame);
    
            //Отрисовка сетки
            for (int i = 0; i < M; i++) {
    
                for (int j = 0; j < N; j++) {
                    net.setPosition(j * 18, i * 18);
                    net.move(45, 90);
                    window.draw(net);
    
                }
            }
    
            //Отрисовка прошлых кубиков
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (field[i][j] == 0) continue;
                    sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                    sprite.setPosition(j * 18, i * 18);
                    sprite.move(45, 90);
                    window.draw(sprite);
                }
            }
    
    
            if (!gameOver()) {
                //Отрисовка текущей фигуры
                for (int i = 0; i < 4; i++) {
                    sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    sprite.setPosition(a[i].x * 18, a[i].y * 18);
                    sprite.move(45, 90);
                    window.draw(sprite);
                }
            }
    
            if (!gameOver()) {
                //Отрисовка следующей фигуры
                for (int i = 0; i < 4; i++) {
                    sprite.setTextureRect(IntRect(colorNum_new * 18, 0, 18, 18));
                    sprite.setPosition((figures[n_new][i] % 2) * 18, (figures[n_new][i] / 2) * 18);
                    sprite.move(255, 120);
                    window.draw(sprite);
                }
            }
    
            // Надпись для следующей фигуры
            Text next("", font, 20);
            next.setFillColor(Color::White);
            next.setStyle(Text::Bold | Text::Italic);
            next.setString("Next figure: ");
            next.setPosition(N * 18 + 60, 95);
            window.draw(next);
    
            //Строка нужная для вывода таймера обратного отсчёта
            std::string str = "To close:";
    
            if (gameOver()) {
    
                //Текст Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Red);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("Game Over!");
                text.setPosition(WIDTH / 2 - 50, HEIGHT / 2 - 50);
    
                //Текст обратного отсчёта
                Text text1("", font, 20);
                text1.setFillColor(Color::Red);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setPosition(WIDTH / 2 - 50, (HEIGHT / 2) + 32 - 50);
    
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
    
            //Текст счёта
            score.str = "Your score is:" + std::to_string(score.num);
            Text text4("", font, 20);
            text4.setFillColor(Color::White);
            text4.setStyle(Text::Bold | Text::Italic);
            text4.setString(score.str);
            text4.setPosition(N * 18 + 60, 65);
            window.draw(text4);

            //Кнопки
            Sprite btn_1(btn_tex);
            FloatRect btn_1_rect = btn_1.getLocalBounds();
            btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
            btn_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            Text text_1("", font, 20);
            text_1.setFillColor(Color::Black);
            text_1.setStyle(Text::Bold);
            if(beginGame_1 != 1) text_1.setString("Restart");
            else text_1.setString("Start");
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
                btn_1.setColor(Color(255,255,255,200));
            }

            if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                btn_2.setColor(Color(255,255,255,200));
            }

            
            window.draw(btn_1);
            window.draw(text_1);
            window.draw(btn_2);
            window.draw(text_2);


    
            
            window.display();

            //Если рестарт
            if (restart == 1) {
                break;
            }
        }
    }while (restart == 1);
};


//Функция проверки проиграна ли игра
bool clTetris::gameOver() {

    for (int i = 0; i < N; i++) {
        if (field[2][i] != 0) {
            return 1;
        }
    }
    return 0;
};

    //Функция проверки выхода за границы поля
bool clTetris::check()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;

    return 1;
};

