#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>
#include "clRaceTheGame.h"

using namespace std;
using namespace sf;

int RGame::getRandomNumber(int a, int b)//Функция создает случайное число 
{
    static bool first = true; if (first) { srand(time(NULL));first = false; }
    int result = a + rand() % ((b + 1) - a);
    result = (result / 10) * 10;
    return result;
}

void GOSound() {
    SoundBuffer gameOver;
    gameOver.loadFromFile("../Audio/crash.wav");
    Sound GameOver;
    GameOver.setBuffer(gameOver);
    GameOver.play();
}

void RGame::RaceTheGame()
{
    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Race The Game");
    //Звук
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("../Audio/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    //Когда GameOver
    Texture gameover;
    gameover.loadFromFile("../Textures/over.png");

    Sprite Gameover(gameover);;
    


    Texture background, racer, obs1, obs2, obs3, obs4;
    Font myfont;
    myfont.loadFromFile("../Font/arial.ttf");

    //Загрузка текстур
    background.loadFromFile("../Textures/road.png");
    racer.loadFromFile("../Textures/racer.png");
    obs1.loadFromFile("../Textures/obs1.png");
    obs2.loadFromFile("../Textures/obs2.png");
    obs3.loadFromFile("../Textures/obs3.png");
    obs4.loadFromFile("../Textures/obs4.png");

    Sprite Background(background), Background1(background), Racer(racer), Obs1(obs1), Obs2(obs2), Obs3(obs3), Obs4(obs4);

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

    bool gameOverBool = 0;

    while (app.isOpen())
    {

        //Счет 
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 15);
        text.setPosition(5, 0);

        //Позиция машины 
        Racer.setPosition(RacerX, RacerY);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);


        if (gameOverBool != 1) {


            //scrolling background 
            Background.setPosition(0, BackgroundY1);
            Background1.setPosition(0, BackgroundY2);
            if (BackgroundY2 > 0)
            {
                BackgroundY1 = 0;
                BackgroundY2 = BackgroundY1 - 500;
            }
            BackgroundY1 += 0.1;
            BackgroundY2 += 0.1;

            //Генератор встречных машин
            if (Obs1Y > SCREEN_HEIGH)
            {
                Obs1Y = 0; Obs1X = getRandomNumber(borderLeft, borderRight); score++;
            }
            else { Obs1Y = Obs1Y + gameSpeed; }
            if (Obs2Y > SCREEN_HEIGH)
            {
                Obs2Y = 0; Obs2X = getRandomNumber(borderLeft, borderRight); score++;
            }
            else { Obs2Y = Obs2Y + gameSpeed; }
            if (Obs3Y > SCREEN_HEIGH)
            {
                Obs3Y = 0; Obs3X = getRandomNumber(borderLeft, borderRight); score++;
            }
            else { Obs3Y = Obs3Y + gameSpeed; }
            if (Obs4Y > SCREEN_HEIGH)
            {
                Obs4Y = 0; Obs4X = getRandomNumber(borderLeft, borderRight); score++;
            }
            else { Obs4Y = Obs4Y + gameSpeed; }

            //Ускоренеи игры с набором игрового уровня 
            if (score > 10 && score < 18) { gameSpeed = 0.15; }
            if (score > 18 && score < 25) { gameSpeed = 0.2; }
            if (score > 25 && score < 35) { gameSpeed = 0.25; }
        }
        //Управление клавиатурой 
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (gameOverBool != 1)
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (RacerX > borderLeft) { RacerX = RacerX - 20; }
                }
                if (gameOverBool != 1)
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (RacerX < borderRight) { RacerX = RacerX + 20; }
                }
                if (gameOverBool != 1)
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (RacerY > 0) { RacerY = RacerY - 20; }
                }
                if (gameOverBool != 1)
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (RacerY < SCREEN_HEIGH - 70) { RacerY = RacerY + 20; }
                }
            }
        }

        //Проверка на столкновение/аварию
        if (((RacerX >= (Obs1X - 30)) && (RacerX <= (Obs1X + 30))) && ((RacerY >= (Obs1Y - 30)) && (RacerY) <= (Obs1Y + 30)))
        {
            GameSound.stop(); 
            
            gameOverBool = 1;
            
        };
        if (((RacerX >= (Obs2X - 30)) && (RacerX <= (Obs2X + 30))) && ((RacerY >= (Obs2Y - 30)) && (RacerY) <= (Obs2Y + 30)))
        {
            GameSound.stop();
          
            gameOverBool = 1;

        };
        if (((RacerX >= (Obs3X - 30)) && (RacerX <= (Obs3X + 30))) && ((RacerY >= (Obs3Y - 30)) && (RacerY) <= (Obs3Y + 30)))
        {
            GameSound.stop();
        
            gameOverBool = 1;
        };
        if (((RacerX >= (Obs4X - 30)) && (RacerX <= (Obs4X + 30))) && ((RacerY >= (Obs4Y - 30)) && (RacerY) <= (Obs4Y + 30)))
        {
            GameSound.stop();
            
            gameOverBool = 1;
        };

        if (gameOverBool != 1) {


            //Прорисовка 
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Racer);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);

            app.draw(text);
            app.display();
        }
        else {
            GOSound();
            Font myfont;
            myfont.loadFromFile("../Font/xirod.ttf");
            stringscore = "YOUR SCORE:" + to_string(score);
            Text text(stringscore, myfont, 30);
            text.setPosition(210, 450);
            app.clear();
            app.draw(Gameover);
            app.draw(text);
            app.display();
        }
    }
}


    int RGame::startGame()
    {
        //TODO
        return 0;
    }

    