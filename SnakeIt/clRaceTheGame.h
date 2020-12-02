#pragma once

#include <string>

class RGame {
public:
    void RaceTheGame();
private:

    const double SCREEN_WIDTH = 800;
    const double SCREEN_HEIGH = 600;
    const int borderLeft = 140;
    const int borderRight = 660;
    const int racerWidth = 40;
    const int racerHeight = 70;
    std::string stringscore = "";
    int score = 0;
    double gameSpeed = 0.15;


    int startGame();
    int getRandomNumber(int, int);
};