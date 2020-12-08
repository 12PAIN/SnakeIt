#pragma once


class clSapper {
public:

    void Sapper(int WEIGHT, int HEIGHT);

private:

    int gridLogic[12][12] = { 0 };
    int gridView[12][12];
    int bombs = 0;
    bool cubeIsOpen[12][12] = { 0 };
    int w = 32;

    bool gameOver();

    void fieldFill(int, int);
    

    
    bool win();





};