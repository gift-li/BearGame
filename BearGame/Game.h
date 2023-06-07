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

	void resizeCharacter(Vector2f);
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
	// current Object
	vector<Object*> mObject;
	// perfoming Object
	Object* mSchedule = nullptr;

	Font font;
	Text textHP;
	Text textScore;
	
	const int MAX_OBJECT = 3;
	// with (1/genProb) chance to generate Obstacle
	int genProb = 15;

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
};