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
	Character();

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

	bool changeHP(int);
	void resize(Vector2f);

	void setInvincible(bool b) { this->isInvincible = b; };
	bool checkInvincible() { return this->isInvincible; };
	Status getStatus() { return this->status; };
	Sprite getSprite() { return this->character; };
	int getHP() { return this->HP; };
private:
	bool loadTexture();
	void setAttribute();

	Sprite character;
	Bear_texture texture;
	int HP = 3;
	Status status = Character::IDLE;

	float jumpHeight;
	float jumpSpeed;
	float g;
	float cd = 5;

	float baseX = 120.f;
	float baseY = 330.f;
	bool idleSwitch = true;
	bool isInvincible = false;
};