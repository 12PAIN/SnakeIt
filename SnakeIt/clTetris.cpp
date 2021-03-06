#include "clTetris.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <SFML/Audio.hpp>
#include <fstream>



using namespace sf;

int highscore;

void clTetris::Tetris(int WIDTH, int HEIGHT) {

    //������������� ���������� ��������
    bool restart = 0;
    std::ifstream fin("TetrisHighscore.txt");
    

    fin >> highscore;
    fin.close();


    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SnakeIt:Tetris");
    do{
        
        restart = 0;

        //������� ����
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                field[i][j] = 0;
            }
        }
    
        //��������� �������
        srand(time(0));

        //���� ����� �� ������ ����
        SoundBuffer click_buffer;
        click_buffer.loadFromFile("../Audio/sounds/menu_click.wav");
        Sound click;
        click.setBuffer(click_buffer);

        //����� ���������� �����
        SoundBuffer line1, line2, line3, line4;
        line1.loadFromFile("../Audio/Nsounds/victory 4.wav");
        line2.loadFromFile("../Audio/Nsounds/victory 1.wav");
        line3.loadFromFile("../Audio/Nsounds/victory 2.wav");
        line4.loadFromFile("../Audio/Nsounds/victory 3.wav");

        Sound l1, l2, l3, l4;
        l1.setBuffer(line1);
        l2.setBuffer(line2);
        l3.setBuffer(line3);
        l4.setBuffer(line4);
        
    
        
    
        //�������� "�����"
        Texture net_tex;
        net_tex.loadFromFile("../Textures/net.png");
        Sprite net(net_tex);
        net.setTextureRect(IntRect(0, 0, 18, 18));
    
        //�������� ����
        Texture background;
        background.setRepeated(true);
        background.loadFromFile("../Textures/background_tetris.png");
        Sprite bground(background);

        Image icon;
        icon.loadFromFile("../Textures/icon_tetris.png");
        window.setIcon(100, 100, icon.getPixelsPtr());

        //�������� �������� ������
        Texture btn_tex;
        btn_tex.loadFromFile("../Textures/button.png");
    
        //�������� �����
        Texture frame_tex;
        frame_tex.loadFromFile("../Textures/frame.png");
        Sprite frame(frame_tex);
        frame.setTextureRect(IntRect(0, 0, 200, 380));
    
        //�����
        Font font;
        font.loadFromFile("../Font/arial.ttf");
    
        //�������� �������� �������
        Texture tex1;
        tex1.setRepeated(true);
        tex1.loadFromFile("../Textures/tex2.png");
    
        //������ �������
        Sprite sprite(tex1);
        sprite.setTextureRect(IntRect(0, 0, 18, 18));
    
        //������������� ��� �������
        Clock clock;
        float timer = 0, delay = 0.3, timer_1 = 0;
    
    
        //��� ������
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

        


    
        //�������� �� �����������
        int dx = 0;

        float dy = 0.3;
    
        //�������
        bool rotate = 0;
    
        //���� ������ �����������?
        bool beginGame = true;
    
        //������� ������� ��� ���������/�������� ������
        int countDeath = 15;
    
        //���� ������
        struct playerScore {
            std::string str;
            int num = 0;
        };
        playerScore score;

        //��������� ��������
        restart = 0;
        beginGame_1 = 1;
    
        while (window.isOpen()) {
    
            //�������������� ��������� ��������. timer_1 ����� ��� ��������� �������. timer - ��� ����� ����� ���������� ����
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            timer_1 += time;
    
            
            Vector2i pos = Mouse::getPosition(window);

            Vector2i wind;
            wind.x = window.getSize().x;
            wind.y = window.getSize().y;
    
    
            //��������� ������������ �������
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
                        
                    }
                    if (event.key.code == Keyboard::S) {
                        beginGame_1 = 0;
                    }
    
                }

                if (event.type == Event::MouseButtonPressed) {
                    if(event.key.code == Mouse::Left){
                        
                        if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                            click.play();
                            if (beginGame_1 != 1) {
                                restart = 1;
                                
                            }
                            else {
                                beginGame_1 = 0;
                            }
                        }

                        if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                            click.play();
                            window.close();
                        }
                    }
                }

            }
            
            
            //�������� �� ��������� �� ����, ����� ����� ������ �� �����������
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
    
                // �������� �� ����������� � ��������� ������ �� �������
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
    
                //������� � ��������� ������ �� �������
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
    
                // �������� ���� � �������� ����� �������
                if (timer > delay && beginGame_1 != 1) {
                    for (int i = 0; i < 4; i++) {
                        b[i] = a[i];
                        a[i].y++;
                    }
    
                    if (!check()) {
    
                        for (int i = 0; i < 4; i++) {
                            field[b[i].y][b[i].x] = colorNum;
                            
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

                //�������� ������ �������
                
                
    
                //��������� ������������ ��������
                dx = 0;
                rotate = 0;
                delay = dy;
    

                //��� ������ ����� ��� �������� ����� ������ ������
                int strCheck = 0;

                //�������� � �������� ����� ������ 
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
                    l4.play();
                }
                else if (strCheck == 3) {
                    score.num += 600;
                    l3.play();
                }
                else if (strCheck == 2) {
                    score.num += 300;
                    l2.play();
                }
                else if (strCheck == 1) {
                    score.num += 100;
                    l1.play();
                }

                strCheck = 0;
            }

            
            if (highscore < score.num) {
                highscore = score.num;
            }

    
            window.clear(Color::White);
    
    
    
            //��������� ����
            window.draw(bground);
    
            //��������� �����
            frame.setPosition(35, 80);
            window.draw(frame);
    
            //��������� �����
            for (int i = 0; i < M; i++) {
    
                for (int j = 0; j < N; j++) {
                    net.setPosition(j * 18, i * 18);
                    net.move(45, 90);
                    window.draw(net);
    
                }
            }
    
            //��������� ������� �������
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
                //��������� ������� ������
                for (int i = 0; i < 4; i++) {
                    sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    sprite.setPosition(a[i].x * 18, a[i].y * 18);
                    sprite.move(45, 90);
                    window.draw(sprite);
                }
            }
    
            if (!gameOver()) {
                //��������� ��������� ������
                for (int i = 0; i < 4; i++) {
                    sprite.setTextureRect(IntRect(colorNum_new * 18, 0, 18, 18));
                    sprite.setPosition((figures[n_new][i] % 2) * 18, (figures[n_new][i] / 2) * 18);
                    sprite.move(255, 160);
                    window.draw(sprite);
                }
            }
            
            std::string hi_str ="Highscore: " + std::to_string(highscore);

            // ������� ������� �����
            Text highscore_text("", font, 20);
            highscore_text.setFillColor(Color::White);
            highscore_text.setStyle(Text::Bold | Text::Italic);
            highscore_text.setString(hi_str);
            highscore_text.setPosition(N * 18 + 60, 95);
            window.draw(highscore_text);


            // ������� ��� ��������� ������
            Text next("", font, 20);
            next.setFillColor(Color::White);
            next.setStyle(Text::Bold | Text::Italic);
            next.setString("Next figure: ");
            next.setPosition(N * 18 + 60, 95 + 40);
            window.draw(next);
    
            //������ ������ ��� ������ ������� ��������� �������
            std::string str = "To close:";
    
            if (gameOver()) {
    
                //����� Game Over
                Text text("", font, 20);
                text.setFillColor(Color::Red);
                text.setStyle(Text::Bold | Text::Underlined);
                text.setString("Game Over!");
                text.setOutlineColor(Color::White);
                FloatRect text_rect = text.getLocalBounds();
                text.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
                text.setOutlineThickness(2);
                text.setPosition(WIDTH / 2, HEIGHT / 2);

                //����� Game Over
                Text text1("", font, 20);
                text1.setFillColor(Color::Red);
                text1.setStyle(Text::Bold | Text::Underlined);
                text1.setOutlineColor(Color::White);


                //�������� ������
                if (timer_1 > 1.0) {
                    countDeath--;
                    timer_1 = 0;
                }

                //������������ ������ ��������� ������� � �������� �������
                str = "To close:" + std::to_string(countDeath);
                text1.setString(str);
                FloatRect text1_rect = text1.getLocalBounds();
                text1.setOrigin(text1_rect.left + text1_rect.width / 2.0f, text1_rect.top + text1_rect.height / 2.0f);
                text1.setOutlineThickness(2);
                text1.setPosition(WIDTH / 2, HEIGHT / 2 + 32);

                window.draw(text1);
                window.draw(text);

                //���������� ��������� ����� ��������� ��������� �������
                if (countDeath == 0) {
                    window.close();
                }
    
            }
    
            //����� �����
            score.str = "Your score is:" + std::to_string(score.num);
            Text text4("", font, 20);
            text4.setFillColor(Color::White);
            text4.setStyle(Text::Bold | Text::Italic);
            text4.setString(score.str);
            text4.setPosition(N * 18 + 60, 65);
            window.draw(text4);

            //������
            Sprite btn_1(btn_tex);
            btn_1.setTextureRect(IntRect(0, 0, 200, 65));
            FloatRect btn_1_rect = btn_1.getLocalBounds();
            btn_1.setOrigin(btn_1_rect.left + btn_1_rect.width / 2.0f, btn_1_rect.top + btn_1_rect.height / 2.0f);
            btn_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            Text text_1("", font, 20);
            text_1.setFillColor(Color::White);
            text_1.setStyle(Text::Bold);
            if(beginGame_1 != 1) text_1.setString("Restart");
            else text_1.setString("Start");
            FloatRect text_1_rect = text_1.getLocalBounds();
            text_1.setOrigin(text_1_rect.left + text_1_rect.width / 2.0f, text_1_rect.top + text_1_rect.height / 2.0f);
            text_1.setPosition(Vector2f(WIDTH / 2.0f - WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));


            Sprite btn_2(btn_tex);
            btn_2.setTextureRect(IntRect(0, 0, 200, 65));
            FloatRect btn_2_rect = btn_2.getLocalBounds();
            btn_2.setOrigin(btn_2_rect.left + btn_2_rect.width / 2.0f, btn_2_rect.top + btn_2_rect.height / 2.0f);
            btn_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            Text text_2("", font, 20);
            text_2.setFillColor(Color::White);
            text_2.setStyle(Text::Bold);
            text_2.setString("Exit");
            FloatRect text_2_rect = text_2.getLocalBounds();
            text_2.setOrigin(text_2_rect.left + text_2_rect.width / 2.0f, text_2_rect.top + text_2_rect.height / 2.0f);
            text_2.setPosition(Vector2f(WIDTH / 2.0f + WIDTH / 8.5333f, HEIGHT - HEIGHT / 4.2352f));

            if ((pos.x >= ((wind.x / 2.0 - wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 - wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                btn_1.setTextureRect(IntRect(0, 65, 200, 65));
            }

            if ((pos.x >= ((wind.x / 2.0 + wind.x / 8.5333) - wind.x / 12.8)) && (pos.x <= ((wind.x / 2.0 + wind.x / 8.5333) + wind.x / 12.8)) && (pos.y >= ((wind.y - wind.y / 4.2352) - wind.y / 22.15)) && (pos.y <= ((wind.y - wind.y / 4.2352) + wind.y / 22.15))) {
                btn_2.setTextureRect(IntRect(0, 65, 200, 65));
            }

            
            window.draw(btn_1);
            window.draw(text_1);
            window.draw(btn_2);
            window.draw(text_2);


    
            
            window.display();

            //���� �������
            if (restart == 1) {
                break;
            }
        }
    }while (restart == 1);
    std::ofstream fout("TetrisHighscore.txt", std::ofstream::out | std::ofstream::trunc);

    fout << highscore;



    fout.close();
};


//������� �������� ��������� �� ����
bool clTetris::gameOver() {

    for (int i = 0; i < N; i++) {
        if (field[2][i] != 0) {
            return 1;
        }
    }
    return 0;
};

    //������� �������� ������ �� ������� ����
bool clTetris::check()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;

    return 1;
};

