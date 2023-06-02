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
	static Game& getInstance() {
		static Game instance;
		return instance;
	};
	void run();

	// watch keyboard event
	void watchEvent();
	void checkCollision();
	// perform obstacle effect
	void doSchedule();
	void update();
	void render();

	Character* getCharacter() { return this->mCharacter; };
	vector<Obstacle*> getObstacle() { return this->mObstacle; };
private:
	Game();
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

	// current Character
	Character* mCharacter;
	// current Obstacles
	vector<Obstacle*> mObstacle;
	// perfoming Obstacle
	Obstacle* scheduleObstacle = nullptr;

	Font font;
	Text textHP;
	Text textScore;

	void pressInput();
	void releaseInput();
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