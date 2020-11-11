#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include "GlobalVars.h"
#include "clTetris.h"
#include "clSapper.h"

using namespace sf;

int main() {
    
    

choice:
    int choice;
    std::cout << "List of games:" << std::endl;
    std::cout << "1.Tetris" << std::endl;
    std::cout << "2.Sapper" << std::endl;
    std::cout << "To select insert number of game!" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1 :{
    TetrisRun:
        clTetris tetris;
        tetris.Tetris(WEIGHT, HEIGHT, &restart);
        if (restart == 1) {
            restart = 0;
            goto TetrisRun;
        }
        break;
    }
    case 2: {
    SapperRun:
        clSapper sapper_app;
        sapper_app.Sapper(WEIGHT, HEIGHT, &restart);
        if (restart == 1) {
            restart = 0;
            goto SapperRun;
        }
        break;
    }
    default: {
        std::cout << "Inserted wrong number!" << std::endl;
        goto choice;
        break;
    }
    
    }

    reselect:
    std::cout << "Want to select another game?" << std::endl;
    std::cout << "Insert 1 if Yes, 0 if No" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1: {
        goto choice;
        break;
    }
    case 0: {
        break;
    }
    default: {
        std::cout << "Inserted wrong digit!" << std::endl;
        goto reselect;
        break;
    }
    }

    
  
    return 0;
}
