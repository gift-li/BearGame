#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Character.h"
#include "Object.h"

using namespace sf;
using namespace std;

class Game
{
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	};
	void drawStartScreen();
	void run();

	// watch keyboard event
	void watchEvent();
	void checkCollision();
	// perform obstacle effect
	void doSchedule();
	void update();
	void render();

	Character* getCharacter() { return this->mCharacter; };
	vector<Object*> getObject() { return this->mObject; };
private:
	Game();
	void restart();
	RenderWindow window;
	Clock clock;
	Clock scoreTimer;
	// loop timer
	float timer = 0;
	// variant to control fps
	float delay = 0.05;
	// score to show
	int timeScore = 0;
	int objectScore = 0;

	// status showing game is continue
	bool gameOn = true;

	bool gameStarted = false;

	// current Character
	Character* mCharacter;
	// current Object
	vector<Object*> mObject;
	// perfoming Object
	Object* mSchedule = nullptr;

	Font font;
	Text textHP;
	Text textScore;
	Text textInvincible;

	Texture explosionTexture;
	Texture goldenCircleTexture;
	
	// with (1/genProb) chance to generate Obstacle
	int genProb = 10;
	const int GEN_CD = 20;
	int genCD = 20;

	void pressInput();
	void releaseInput();
	// update mCharacter
	void updateCharacter();
	// dice to generate Object
	void genObject();
	// update each Object's position in mObject
	void updateObject();

	void initText();
	void updateTextHP();
	void updateTextScore();
	void updateTextInvincible();
};