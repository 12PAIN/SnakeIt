#pragma once
class clSnake {
public:

    void Snake(int WIDTH, int HEIGHT);

private:

    void gameAction();

    int SIZE = 30;
    int vx = SIZE * SIZE;
    int vy = SIZE * 15;
    int horizontalline = 30;
    int verticalline = 15;
    int direction = 2;
    int num = 3;
    bool gameOver = 0;
    bool restart;

    struct Snake
    {
        int x, y;
    } snake[100];

    

    struct
    {
        int x, y;
    }apple;




};