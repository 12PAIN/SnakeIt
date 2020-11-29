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
        myfont.loadFromFile("Font/xirod.ttf");
        stringscore = "YOUR SCORE:" + to_string(score);
        Text text(stringscore, myfont, 30);
        text.setPosition(210, 450);
        app.clear();
        app.draw(Gameover);
        app.draw(text);
        app.display();

    }


    int main()
    {
        //Звук
        SoundBuffer gameSoundBuffer;
            gameSoundBuffer.loadFromFile("Audio/game.wav");
        Sound GameSound;
            GameSound.setBuffer(gameSoundBuffer);


        Texture background, racer, obs1, obs2, obs3, obs4, gameover;
        Font myfont;
        myfont.loadFromFile("Font/xirod.ttf");

        //Загрузка текстур
        if (!background.loadFromFile("Texture/background.png")) return EXIT_FAILURE;
        if (!racer.loadFromFile("Texture/racer.png")) return EXIT_FAILURE;
        if (!obs1.loadFromFile("Texture/obs1.png")) return EXIT_FAILURE;
        if (!obs2.loadFromFile("Texture/obs2.png")) return EXIT_FAILURE;
        if (!obs3.loadFromFile("Texture/obs3.png")) return EXIT_FAILURE;
        if (!obs4.loadFromFile("Texture/obs4.png")) return EXIT_FAILURE;

        Sprite Background(background), Background1(background), Racer(racer), Obs1(obs1), Obs2(obs2), Obs3(obs3), Obs4(obs4), Gameover(gameover);

        double RacerX, RacerY, Obs1X, Obs1Y, Obs2X, Obs2Y, Obs3X, Obs3Y, Obs4X, Obs4Y;

        //Позиции машин и гонщика 
        RacerX = SCREEN_WIDTH / 2;
        RacerY = SCREEN_HEIGH - racerHeight;
        Obs1X = getRandomNumber(borderLeft, borderRight);
        Obs2X = getRandomNumber(borderLeft, borderRight);
        Obs3X = getRandomNumber(borderLeft, borderRight);
        Obs4X = getRandomNumber(borderLeft, borderRight);
        Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300;
        double BackgroundY1 = 0;
        double BackgroundY2 = -600;

        GameSound.play();
        GameSound.setLoop(true);

    }

}