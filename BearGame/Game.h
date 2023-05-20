#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Game
{
public:
	Game();
	~Game() = default;

	void run();

	void watchEvent();
	void update();
	void render();

	void setCharacter();
	// void deleteCharacter();

	void addObstacle();
	void deleteObstacle();
private:
	void proccessInput();

	RenderWindow window;

	Texture texture;

	Sprite mcharacter;
	vector<class Obstacle*> mObstacle;
};