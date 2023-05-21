#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

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
private:
	bool loadTexture(Type);
	void setTexture(Type);

	Sprite character;
	custom_texture texture;
	int hp;
	Status status;
};

struct custom_texture
{
	Texture bear;
};