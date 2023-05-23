#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

struct Character_texture
{
	Texture bear;
};

class Character
{
public:
	enum Type
	{
		Bear
	};
	enum Status
	{
		JUMP,
		SQUAT,
		IDLE
	};
	Character(Type);

	// check method: whether collide with input
	bool collide(Sprite);
	// trigger event: when collide success
	void hit();
	// action method: jump
	void jump();
	// action method: squat
	void squat();
	// action method: idle
	void idle();
	// get current status
	Status getStatus();

	Sprite getSprite();

	int getHP();
private:
	bool loadTexture(Type);
	void setTexture(Type);
	void setScale(Type);
	void reduceHP();

	Sprite character;
	Character_texture texture;
	int HP;
	Status status;
};