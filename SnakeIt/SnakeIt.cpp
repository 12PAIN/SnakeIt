#include <SFML/Graphics.hpp>
#include <iostream>

const int WEIGHT = 1280;
const int HEIGHT = 720;

using namespace sf;

void Run();
void Draw();

int main(){   

    Run();
    
    return 0;
}

void Run() {
    Draw();
}

void Draw() {

    RenderWindow window(VideoMode(WEIGHT, HEIGHT), "SnakeIt");

    while (window.isOpen()){

        Event event;
        while (window.pollEvent(event)){
            
            if (event.type == Event::Closed)
                window.close();

        }

        window.clear(Color(250, 200, 100, 0));

        RectangleShape menuFone(Vector2f((WEIGHT / 5), (HEIGHT)));
        menuFone.setFillColor(Color(230, 230, 230, 255));
        window.draw(menuFone);


        window.display();

    }
}
