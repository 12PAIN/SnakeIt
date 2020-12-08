#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include <string>
#include "clRaceTheGame.h"
#include <fstream>


using namespace std;
using namespace sf;

const int WIDTH = 1280;
const int HEIGHT = 720;

int RGame::getRandomNumber(int a, int b)//Функция создает случайное число 
{
    static bool first = true; if (first) { srand(time(NULL));first = false; }
    int result = a + rand() % ((b + 1) - a);
    result = (result / 10) * 10;
    return result;
}

void RGame::RaceTheGame()
{
    bool restart = 0;
    
    ifstream fin("RaceHighscore.txt");
    int highscore;
    fin >> highscore;
    fin.close();

    do {

        bool beginGame = 1;
        restart = 0;
        score = 0;
        RenderWindow app(VideoMode(1280, 720), "Race The Game");
        
        double RacerX, RacerY, Obs1X, Obs1Y, Obs2X, Obs2Y, Obs3X, Obs3Y, Obs4X, Obs4Y;
        bool speedupBool = 0;
        bool slowDown = 0;
        float speedup = 0, slowdown = 0;

        //Звук
        SoundBuffer gameSoundBuffer;
        gameSoundBuffer.loadFromFile("../Audio/game.wav");
        Sound GameSound;
        GameSound.setBuffer(gameSoundBuffer);

        //Звук клика по кнопке меню
        SoundBuffer click_buffer;
        click_buffer.loadFromFile("../Audio/sounds/menu_click.wav");
        Sound click;
        click.setBuffer(click_buffer);

        //Шрифт
        Font font;
        font.loadFromFile("../Font/arial.ttf");

        //Текстура кнопки
        Texture btn_tex;
        btn_tex.loadFromFile("../Textures/button.png");

        //Когда GameOver
        Texture gameover;
        gameover.loadFromFile("../Textures/over.png");
        Sprite Gameover(gameover);

        //Фон
        Texture fone;
        fone.loadFromFile("../Textures/background_race.png");
        Sprite Fone(fone);

        //Звук GO
        SoundBuffer gameOver;
        gameOver.loadFromFile("../Audio/crash.wav");
        Sound GameOver;
        GameOver.setBuffer(gameOver);

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

        //Позиции машин и гонщика 
        RacerX = SCREEN_WIDTH / 2;
        RacerY = SCREEN_HEIGH - racerHeight - 50;
        Obs1X = getRandomNumber(borderLeft, borderRight);
        Obs2X = getRandomNumber(borderLeft, borderRight);
        Obs3X = getRandomNumber(borderLeft, borderRight);
        Obs4X = getRandomNumber(borderLeft, borderRight);
        Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300;
        double BackgroundY1 = 0;
        double BackgroundY2 = -600;

        GameSound.setVolume(15.f);
        GameSound.setPitch(1.4);
        
        GameSound.setLoop(true);

        bool gameOverBool = 0;

        Clock clock;
        float timer = 0, delay = 0.0001,timer_1 = 0;

        while (app.isOpen())
        {
            Vector2i pos = Mouse::getPosition(app);

            Vector2i wind;
            wind.x = app.getSize().x;
            wind.y = app.getSize().y;

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();

            timer += time;
            timer_1 += time;

            speedupBool = 0, slowDown = 0;
            speedup = 0, slowdown = 0;

            //Счет 
            stringscore = "SCORE:" + to_string(score);
            Text text(stringscore, myfont, 23);
            text.setPosition(5, 20);
            string stringscore1 = "HIGHSCORE:" + to_string(highscore);
            Text text3(stringscore1, myfont, 23);
            text3.setPosition(5, 0);


            //Позиция машины 
            Racer.setPosition(RacerX, RacerY);
            Obs1.setPosition(Obs1X, Obs1Y);
            Obs2.setPosition(Obs2X, Obs2Y);
            Obs3.setPosition(Obs3X, Obs3Y);
            Obs4.setPosition(Obs4X, Obs4Y);


            if (timer > delay) {
                //scrolling background 
                Background.setPosition(0, BackgroundY1);
                Background1.setPosition(0, BackgroundY2);
                if (BackgroundY2 > 0)
                {
                    BackgroundY1 = 0;
                    BackgroundY2 = BackgroundY1 - 500;
                }
            }
            if (gameOverBool != 1 && beginGame != 1 && timer > delay) {


                timer = 0;

                //Генератор встречных машин
                if (Obs1Y > SCREEN_HEIGH)
                {
                    Obs1Y = -100; Obs1X = getRandomNumber(borderLeft, borderRight); score++;
                }
                else { Obs1Y = Obs1Y + gameSpeed; }
                if (Obs2Y > SCREEN_HEIGH)
                {
                    Obs2Y = -100; Obs2X = getRandomNumber(borderLeft, borderRight); score++;
                }
                else { Obs2Y = Obs2Y + gameSpeed; }
                if (Obs3Y > SCREEN_HEIGH)
                {
                    Obs3Y = -100; Obs3X = getRandomNumber(borderLeft, borderRight); score++;
                }
                else { Obs3Y = Obs3Y + gameSpeed; }
                if (Obs4Y > SCREEN_HEIGH)
                {
                    Obs4Y = -100; Obs4X = getRandomNumber(borderLeft, borderRight); score++;
                }
                else { Obs4Y = Obs4Y + gameSpeed; }


            }


            if (GameSound.getStatus() == 0 && beginGame != 1) {
                GameSound.play();
            }

            //Управление
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed) app.close();

                if (event.type == Event::MouseButtonPressed) {

                    if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 18.) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 18.) + wind.y / 22.15))) {
                        click.play();
                        if (beginGame == 1) {
                            beginGame = 0;
                        }
                        else {
                            gameOverBool = 0;
                            restart = 1;
                        }
                    }

                    if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 18.) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 18.) + wind.y / 22.15))) {
                        click.play();
                        app.close();
                    }


                }

                if (event.type == sf::Event::KeyPressed)
                {

                    if (gameOverBool != 1 && beginGame != 1)
                        if (event.key.code == sf::Keyboard::Left)
                        {
                            if (RacerX > borderLeft) { RacerX = RacerX - 20; }
                        }
                    if (gameOverBool != 1 && beginGame != 1)
                        if (event.key.code == sf::Keyboard::Right)
                        {
                            if (RacerX < borderRight) { RacerX = RacerX + 20; }
                        }
                    if (gameOverBool != 1 && beginGame != 1)
                        if (event.key.code == sf::Keyboard::Up)
                        {

                            speedupBool = 1;

                        }
                    if (gameOverBool != 1 && beginGame != 1)
                        if (event.key.code == sf::Keyboard::Down)
                        {
                            slowDown = 1;
                        }
                    
                    if (event.key.code == sf::Keyboard::R)
                    {
                        gameOverBool = 0;
                        restart = 1;
                    }
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        app.close();
                    }
                    if (event.key.code == sf::Keyboard::S)
                    {
                        beginGame = 0;
                    }

                }

                if (event.type == Event::KeyReleased) {
                    if (gameOverBool != 1 && beginGame != 1)
                        if (event.key.code == sf::Keyboard::Up)
                        {

                            speedupBool = 0;

                        }
                    if (gameOverBool != 1 && beginGame != 1)
                        if (event.key.code == sf::Keyboard::Down)
                        {
                            slowDown = 0;
                        }
                }

            }


            

            //Ускоренеи игры с набором игрового уровня 

            if (speedupBool == 1) speedup = 1;
            else speedup = 0;
            if (slowDown == 1) slowdown = 1;
            else slowdown = 0;

            if (score < 600) {
                gameSpeed = 0.10 + (score / 3 * 0.001);
                if (speedup == 1 && slowdown != 1) gameSpeed += 0.3;
                //else gameSpeed -= 0.1;
                
            }

            if (speedup == 1 && timer_1 > 0.1) {
                speedup = 0;
                timer_1 = 0;
                score++;
                
            }

            if (beginGame != 1) {
                BackgroundY1 += (gameSpeed - 0.07 - speedup * 0.05 + slowdown * 0.05);
                BackgroundY2 += (gameSpeed - 0.07 - speedup * 0.05 + slowdown * 0.05);
            }

            //Проверка на столкновение/аварию
            if (((RacerX >= (Obs1X - 30)) && (RacerX <= (Obs1X + 30))) && ((RacerY >= (Obs1Y - 30)) && (RacerY) <= (Obs1Y + 30)))
            {
                GameSound.stop();
                if (gameOverBool != 1) GameOver.play();
                gameOverBool = 1;

            };
            if (((RacerX >= (Obs2X - 30)) && (RacerX <= (Obs2X + 30))) && ((RacerY >= (Obs2Y - 30)) && (RacerY) <= (Obs2Y + 30)))
            {
                GameSound.stop();
                if (gameOverBool != 1) GameOver.play();
                gameOverBool = 1;

            };
            if (((RacerX >= (Obs3X - 30)) && (RacerX <= (Obs3X + 30))) && ((RacerY >= (Obs3Y - 30)) && (RacerY) <= (Obs3Y + 30)))
            {
                GameSound.stop();
                if (gameOverBool != 1) GameOver.play();
                gameOverBool = 1;
            };
            if (((RacerX >= (Obs4X - 30)) && (RacerX <= (Obs4X + 30))) && ((RacerY >= (Obs4Y - 30)) && (RacerY) <= (Obs4Y + 30)))
            {
                GameSound.stop();
                if (gameOverBool != 1) GameOver.play();
                gameOverBool = 1;
            };

            if (gameOverBool != 1) {


                //Прорисовка 
                app.clear();

                Background.move(240, 60);
                Background1.move(240, 60);
                Racer.move(240, 60);
                Obs1.move(240, 60);
                Obs2.move(240, 60);
                Obs3.move(240, 60);
                Obs4.move(240, 60);
                text.move(240, 60);
                text3.move(240, 60);

                app.draw(Background);
                app.draw(Background1);
                app.draw(Racer);
                app.draw(Obs1);
                app.draw(Obs2);
                app.draw(Obs3);
                app.draw(Obs4);
                app.draw(text);
                app.draw(text3);
                app.draw(Fone);
                
            }
            else {

                
                stringscore = "Your score:" + to_string(score);
                Text text(stringscore, font, 30);
                text.setPosition(260, 440);
                stringscore = "Your highscore:" + to_string(highscore);
                Text text1(stringscore, font, 30);
                text1.setPosition(260, 480);
                app.clear();

                Gameover.setPosition(240, 60);
                text.move(240, 60);
                text1.move(240, 60);

                app.draw(Fone);
                app.draw(Gameover);
                app.draw(text);
                app.draw(text1);

                
                
            }


            //Кнопки
            Sprite btn_1(btn_tex);
            btn_1.setTextureRect(IntRect(0, 0, 200, 65));
            FloatRect btn_1_rect = btn_1.getLocalBounds();
            btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
            btn_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 18.));

            Text text_1("", font, 20);
            text_1.setFillColor(Color::White);
            text_1.setStyle(Text::Bold);
            if (beginGame != 1) text_1.setString("Restart");
            else text_1.setString("Start");
            FloatRect text_1_rect = text_1.getLocalBounds();
            text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
            text_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 18.));


            Sprite btn_2(btn_tex);
            btn_2.setTextureRect(IntRect(0, 0, 200, 65));
            FloatRect btn_2_rect = btn_2.getLocalBounds();
            btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
            btn_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 18.));

            Text text_2("", font, 20);
            text_2.setFillColor(Color::White);
            text_2.setStyle(Text::Bold);
            text_2.setString("Exit");
            FloatRect text_2_rect = text_2.getLocalBounds();
            text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
            text_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 18.));

            if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 18.) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 18.) + wind.y / 22.15))) {
                btn_1.setTextureRect(IntRect(0, 65, 200, 65));
            }

            if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 18.) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 18.) + wind.y / 22.15))) {
                btn_2.setTextureRect(IntRect(0, 65, 200, 65));
            }


            app.draw(btn_1);
            app.draw(text_1);
            app.draw(btn_2);
            app.draw(text_2);

            app.display();
            
            if (score > highscore) {
                highscore = score;
            }

            if (restart == 1){
                break;
            }
        }
    }while (restart == 1);

    ofstream fout("RaceHighscore.txt", std::ofstream::out | std::ofstream::trunc);
    fout << highscore;
    fout.close();

}


    int RGame::startGame()
    {
        //TODO
        return 0;
    }

    