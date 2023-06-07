#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Object
{
public:
	enum Type
	{
		TREE,
		EAGLE,
		POTION,
		HERB,
		HONEY,

		// Don't remove: add enum entity above
		LAST
	};

	Object() = default;
	~Object() = default;
	// move
	void move() { this->sprite.move(-speedx, 0); };
	// perform
	virtual void perform() {};
	virtual void restore() {};

	static Object* random();

	bool isItem();

	Sprite getSprite() { return this->sprite; };
	Texture getTexture() { return this->texture; };
	int getDamage() { return this->damage; };
	void getDamage(int input) { this->damage = input; };
	Type getType() { return this->type; };
	void setType(Type type) { this->damage = type; };
	void setWindowSize(unsigned int window_width) { this->window_width = window_width; };
	unsigned int getWindowSize() { return this->window_width; };
	void setSpeedX(int speedx) { this->speedx = speedx; };
	int getPoint() { return this->point; };
	void setPoint(float point) { this->damage = point; };
	int getRatio() { return this->point_ratio; };
	int getInterval() { return this->interval; };
	int minusInterval(int offset) { this->interval -= offset; };
	bool checkAlive() { return this->isAlive; };
	void setAlive(bool isAlive) { this->isAlive = isAlive; };
protected:
	virtual void setAttribute() {};

	Sprite sprite;
	Texture texture;

	Type type = Object::HONEY;
	unsigned int window_width = 1440;
	// position
	Vector2f scale;
	// x-axis moving speed
	float speedx = 0;
	// on hit damage
	int damage = 0;
	// credit point if not alive
	int point = 0;
	// add ratio if destroyed by item
	int point_ratio = 1;
	// item effect time counter
	int interval = 1;
	// whether item effect is trigger
	bool isTrigger = false;
	// check object still alive;
	bool isAlive = true;
};
