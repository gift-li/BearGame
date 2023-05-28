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

	void run();

	void watchEvent();
	void checkCollision();
	void update();
	void render();
private:
	void restart();
	RenderWindow window;
	Clock clock;
	// loop timer
	float timer = 0;
	// variant to control fps
	float delay = 0.05;
	// score to show
	int score = 0;

	// status showing game is continue
	bool gameOn = true;

	Character* mCharacter;
	vector<Obstacle*> mObstacle;

	Font font;
	Text textHP;
	Text textScore;

	void pressInput();
	// can generate Obstacle when equals 0
	int genCD = 0;
	// with (1/genProb) chance to generate Obstacle
	int genProb = 10;
	// update mCharacter
	void updateCharacter();
	// dice to generate Obstacle
	void generateObstacle();
	// update each Obstacle's position in mObstacle
	void updateObstacle();

	void initText();
	void updateTextHP();
	void updateTextScore();
};