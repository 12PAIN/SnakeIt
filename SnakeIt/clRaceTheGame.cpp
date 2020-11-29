#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

const double SCREEN_WIDTH = 800;
const double SCREEN_HEIGH = 600;
const int borderLeft = 140;
const int borderRight = 660;
const int racerWidth = 40;
const int racerHeight = 70;
string stringscore = "";
int score = 0;
double gameSpeed = 0.3;

RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Race The Game");

int getRandomNumber(int a, int b)//Функция создает случайное число 
{
    static bool first = true; if (first) { srand(time(NULL));first = false; }
    int result = a + rand() % ((b + 1) - a);
    result = (result / 10) * 10;
    return result;
}

int gameOver()//Функция gameover(Спасибо, кэп)
{
    Texture gameover;
    if (!gameover.loadFromFile("Textures/over.png")) return EXIT_FAILURE;

    Sprite Gameover(gameover);;
    SoundBuffer gameOver;
    gameOver.loadFromFile("audio/crash.wav");
    Sound GameOver;
    GameOver.setBuffer(gameOver);
    GameOver.play();
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        Font myfont;
        myfont.loadFromFile("Font/arial.ttf");
        stringscore = "YOUR SCORE:" + to_string(score);
        Text text(stringscore, myfont, 30);
        text.setPosition(210, 450);
        app.clear();
        app.draw(Gameover);
        app.draw(text);
        app.display();

    }

}