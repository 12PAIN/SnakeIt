#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>

const int WEIGHT = 1280;
const int HEIGHT = 720;

using namespace sf;

bool restart = 0;

class clTetris {

public:
    void Tetris() {


        srand(time(0));

        RenderWindow window(VideoMode(WEIGHT, HEIGHT), "SnakeIt");

        //Загрузка "сетки"
        Texture net_tex;
        net_tex.loadFromFile("../Textures/net.png");
        Sprite net(net_tex);
        net.setTextureRect(IntRect(0, 0, 18, 18));

        //Загрузка фона
        Texture background;
        background.setRepeated(true);
        background.loadFromFile("../Textures/background.png");
        Sprite bground(background);

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
        int colorNum = 1;
        Sprite sprite(tex1);
        sprite.setTextureRect(IntRect(0, 0, 18, 18));

        //Инициализация для таймера
        Clock clock;
        float timer = 0, delay = 0.3, timer_1 = 0;


        //Тип фигуры
        int n = rand() % 7;

        //Движение по горизонтали
        int dx = 0;

        //Поворот
        bool rotate = 0;

        //Игра только запустилась?
        bool beginGame = true;

        //Счётчик таймера для проигрыша/Обратный отсчёт
        int countDeath = 15;

        //Счёт игрока
        struct playerScore {
            std::string str;
            int num;
        };

        playerScore score;
        score.num = 0;


        while (window.isOpen()) {

            //Первоначальная настройка таймеров. timer_1 нужен для обратного отсчёта. timer - для счёта когда спускаться вниз
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            timer_1 += time;




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

                }
            }

            //Проверка не проиграна ли игра, чтобы новые кубики не создавались
            if (!gameOver()) {

                // Движение по горизонтали с проверкой выхода за границы
                for (int i = 0; i < 4; i++) {
                    b[i] = a[i];
                    a[i].x += dx;
                }

                if (!check())
                    for (int i = 0; i < 4; i++) {
                        a[i] = b[i];
                    }

                //Поворот с проверкой выхода за границы
                if (rotate) {
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
                if (timer > delay) {
                    for (int i = 0; i < 4; i++) {
                        b[i] = a[i];
                        a[i].y++;
                    }

                    if (!check()) {

                        for (int i = 0; i < 4; i++) {
                            field[b[i].y][b[i].x] = colorNum;
                        }

                        colorNum = 1 + rand() % 7;
                        n = rand() % 7;
                        for (int i = 0; i < 4; i++) {
                            a[i].x = figures[n][i] % 2;
                            a[i].y = figures[n][i] / 2;
                        }

                    }

                    timer = 0;
                }

                //Создание первых кубиков
                if (beginGame) {

                    beginGame = false;
                    n = rand() % 7;
                    for (int i = 0; i < 4; i++) {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                    }

                }

                //Обнуление используемых значений
                dx = 0;
                rotate = 0;
                delay = 0.3;

                //Проверка и убирание целой полосы кубиков
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
                    else { score.num += 100; }
                }
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

            //Отрисовка текущей фигуры
            for (int i = 0; i < 4; i++) {
                sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                sprite.setPosition(a[i].x * 18, a[i].y * 18);
                sprite.move(45, 90);
                window.draw(sprite);
            }

            //Строка нужная для вывода таймера обратного отсчёта
            std::string str = "To close:";

            if (gameOver()) {

                //Текст Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Red);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("Game Over!");
                text.setPosition(WEIGHT / 2, HEIGHT / 2);

                //Текст обратного отсчёта
                Text text1("", font, 20);
                text1.setFillColor(Color::Red);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setPosition(WEIGHT / 2, (HEIGHT / 2) + 32);

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


            Text text2("", font, 20);
            text2.setFillColor(Color::Black);
            text2.setStyle(Text::Bold | Text::Italic);
            text2.setString("To exit press ESC");
            text2.setPosition(N * 18 + 5, 10);
            window.draw(text2);

            Text text3("", font, 20);
            text3.setFillColor(Color::Black);
            text3.setStyle(Text::Bold | Text::Italic);
            text3.setString("To restart press R");
            text3.setPosition(N * 18 + 5, 35);
            window.draw(text3);

            //Текст результата
            score.str = "Your score is:" + std::to_string(score.num);
            Text text4("", font, 20);
            text4.setFillColor(Color::Black);
            text4.setStyle(Text::Bold | Text::Italic);
            text4.setString(score.str);
            text4.setPosition(N * 18 + 60, 65);
            window.draw(text4);


            window.display();
        }
    }
private:

    static const int M = 20; // высота игрового поля
    static const int N = 10; // ширина игрового поля

    //Логическая часть поля
    int field[M][N] = { 0 };

    int figures[7][4] =
    {
        1,3,5,7, // I
        2,4,5,7, // S
        3,5,4,6, // Z
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };

    //Структура для вывода блоков с вспомогательными массивами
    struct Point
    {
        int x, y;
    } a[4], b[4];


    //Функция проверки проиграна ли игра
    bool gameOver() {

        for (int i = 0; i < N; i++) {
            if (field[2][i] != 0) {
                return 1;
            }
        }
        return 0;
    }

    //Функция проверки выхода за границы поля
    bool check()
    {
        for (int i = 0; i < 4; i++)
            if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
            else if (field[a[i].y][a[i].x]) return 0;

        return 1;
    }


};

int main() {
    clTetris tetris;
    int choice;

choice:
    
    std::cout << "List of games:" << std::endl;
    std::cout << "1.Tetris" << std::endl;
    std::cout << "To select insert number of game!" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1 :{
    TetrisRun:
        tetris.Tetris();
        if (restart == 1) {
            restart = 0;
            goto TetrisRun;
        }
        break;
    }
    default: {
        std::cout << "Inserted wrong number!" << std::endl;
        goto choice;
        break;
    }
    
    }

    reselect:
    std::cout << "Want to select another game?" << std::endl;
    std::cout << "Insert 1 if Yes, 0 if No" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1: {
        goto choice;
        break;
    }
    case 0: {
        break;
    }
    default: {
        std::cout << "Inserted wrong digit!" << std::endl;
        goto reselect;
        break;
    }
    }


  
    return 0;
}
