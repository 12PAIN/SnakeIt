#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include "GlobalVars.h"
#include "clTetris.h"
#include "clSapper.h"
#include "menu.h"
#include "clSnake.h"

using namespace sf;

int main() {

    /*
    clSnake snake;

    snake.Snake(WIDTH, HEIGHT);
    */
    
    clMenu menu;

    menu.menu(WIDTH, HEIGHT);
    

    return 0;
}
