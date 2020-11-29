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