#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Character.h"
#include "Obstacle.h"

using namespace sf;
using namespace std;

class Game
{
public:
	Game();
	~Game() = default;

	void run();

	void watchEvent();
	void checkCollision();
	void update();
	void render();

	void setCharacter();
	// void deleteCharacter();

	void addObstacle();
	void deleteObstacle();
private:
	void pressInput();
	void releaseInput();

	RenderWindow window;
	Clock clock;

	Character mCharacter;
	vector<Obstacle> mObstacle;
};