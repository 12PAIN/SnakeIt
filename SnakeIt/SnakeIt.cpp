#include <SFML/Graphics.hpp>
#include <iostream>

const int WEIGHT = 500;
const int HEIGHT = 500;

const int M = 20; // высота игрового поля
const int N = 10; // ширина игрового поля

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

struct Point
{
    int x, y;
} a[4], b[4];

using namespace sf;

void Run();
void Draw();

int main(){   

    Run();
    
    return 0;
}

void Run() {
    Draw();
}

void Draw() {

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(WEIGHT, HEIGHT), "SnakeIt");

    Texture tex1;
    tex1.setRepeated(true);
    tex1.loadFromFile("E:\\Study\\SnakeIt\\Textures\\tex1.png");

    Sprite sprite(tex1);
    sprite.setTextureRect(IntRect(0, 0, 18, 18));

    Clock clock;

    float timer = 0, delay = 0.3;

    int dx = 0;
    bool rotate = 0;

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        window.clear(Color::White);

        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close();
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

            }
        }

        for (int i = 0; i < 4; i++) a[i].x += dx;

        if (rotate) {
            Point p = a[1];
            for (int i = 0; i < 4; i++) {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
        }

        if (timer > delay) {
            for (int i = 0; i < 4; i++) {
                a[i].y++;
            }
            timer = 0;
        }

        int n = 3; 

        if (a[0].x == 0)
        for (int i = 0; i < 4; i++)
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }

        dx = 0;
        rotate = 0;

        for (int i = 0; i < 4; i++)
        {
            // Устанавливаем позицию каждого кусочка тетрамино
            sprite.setPosition(a[i].x * 18, a[i].y * 18);
            // Отрисовка спрайта
            window.draw(sprite);
        }

        window.display();
    }
}