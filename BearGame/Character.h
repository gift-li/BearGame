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

	void reset();
	// check method: whether collide with input
	bool collide(Sprite);
	// action method: jump
	void jump();
	// action method: squat
	void squat();
	// action method: idle
	void idle();
	// get current status
	void move();
	// keep moving
	Status getStatus();

	Sprite getSprite();

	int getHP();
	void changeHP(int);
private:
	bool loadTexture(Type);
	void setTexture(Type);

	Sprite character;
	Character_texture texture;
	int HP;
	Status status = Character::IDLE;

	float jumpHeight;
	float jumpSpeed;
	float g;
};