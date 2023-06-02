#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

struct Bear_texture
{
	Texture idle1;
	Texture idle2;
	Texture jump;
	Texture squat;
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

	void idleMove();
	void jumpMove();
	void squatMove();
	void resetMove();

	void setInvincible(bool b) { this->isInvincible = b; };
	bool checkInvincible() { return this->isInvincible; };
	Status getStatus() { return this->status; };
	Sprite getSprite() { return this->character; };
	int getHP() { return this->HP; };
	void changeHP(int offset) { this->HP -= offset; };
private:
	bool loadTexture(Type);
	void setAttribute(Type);

	Sprite character;
	Bear_texture texture;
	int HP;
	Status status = Character::IDLE;

	float jumpHeight;
	float jumpSpeed;
	float g;
	float cd = 5;

	bool idleSwitch = true;
	bool isInvincible = false;
};