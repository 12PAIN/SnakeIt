#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;

const int W = 600;
const int H = 480;
int speed = 4;//Добавить сложности 3-easy mod 4-medium mod 5-hard mod
bool field[W][H] = { 0 };

struct player
{
	int x, y, dir;
	Color color;
	player(Color c)
	{
		x = rand() % W;
		y = rand() % H;
		color = c;
		dir = rand() % 4;
	}
	void tick()
	{
		if (dir == 0) y += 1;
		if (dir == 1) x -= 1;
		if (dir == 2) x += 1;
		if (dir == 3) y -= 1;

		if (x >= W) x = 0; if (x < 0) x = W - 1;
		if (y >= H) y = 0; if (y < 0) y = H - 1;
	}

	Vector3f getColor()
	{
		return Vector3f(color.r, color.g, color.b);
	}
};

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(W, H), "Tron The Game!");
	window.setFramerateLimit(60);

	Texture texture;
	texture.loadFromFile("Textures/background.jpg");
	Sprite sBackground(texture);

	player p1(Color::Red), p2(Color::Green);//Сделать так чтобы пользователь мог сам выбирать цвет 

	Sprite sprite;
	RenderTexture t;
	t.create(W, H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear(); t.draw(sBackground);


	Font font; font.loadFromFile("Font/arial.ttf");
	Text textWin("WIN", font, 35);
	Text textLose("LOSE", font, 35);
	Text textPlayer1("PLAYER ", font, 35);//Надпись и ее размер
	Text textPlayer2("PLAYER ", font, 35);
	textPlayer1.setPosition(W / 2 - 125, 30);//Координаты вывода этой надписи
	textPlayer2.setPosition(W / 2 - 125, 60);
	textWin.setPosition(W / 2 + 25, 30);
	textLose.setPosition(W / 2 + 25, 60);

	bool Game = 1;//Что выводит игра при работе 

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))  if (p1.dir != 2) p1.dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) if (p1.dir != 1) p1.dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up))    if (p1.dir != 0) p1.dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down))  if (p1.dir != 3) p1.dir = 0;

		if (Keyboard::isKeyPressed(Keyboard::A)) if (p2.dir != 2) p2.dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::D)) if (p2.dir != 1) p2.dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::W)) if (p2.dir != 0) p2.dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::S)) if (p2.dir != 3) p2.dir = 0;

		if (!Game)//Что выводит игра после завершения 
		{
			window.draw(textWin);//Выводит текст YOU WIN!
			window.draw(textLose);
			window.draw(textPlayer1);
			window.draw(textPlayer2);
			window.display();
			continue;
		}

		for (int i = 0; i < speed;i++)
		{
			p1.tick(); p2.tick();
			if (field[p1.x][p1.y] == 1) { Game = 0; textPlayer1.setFillColor(p2.color), textWin.setFillColor(Color::White); textPlayer2.setFillColor(p1.color), textLose.setFillColor(Color::White); }//Player(цвет игрока) win
			if (field[p2.x][p2.y] == 1) { Game = 0; textPlayer1.setFillColor(p1.color), textWin.setFillColor(Color::White); textPlayer2.setFillColor(p2.color), textLose.setFillColor(Color::White); }//Player(цвет игрока) lose
			field[p1.x][p1.y] = 1;
			field[p2.x][p2.y] = 1;

			CircleShape c(3);
			c.setPosition(p1.x, p1.y); c.setFillColor(p1.color); t.draw(c);
			c.setPosition(p2.x, p2.y); c.setFillColor(p2.color); t.draw(c);
			t.display();
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}