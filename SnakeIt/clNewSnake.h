#pragma once

class NewSnake {
public:

    void Snake();

private:

    int N = 30, M = 20;
    int size = 16;
    int w = size * N;
    int h = size * M;

    int dir, num = 4;

    struct Snake
    {
        int x, y;
    }  s[100];

    struct Fruit
    {
        int x, y;
    } f;

    void Tick();


};