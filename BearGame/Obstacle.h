#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Obstacle texture (image)
struct Obstacle_texture
{
	Texture tree;
	Texture eagle;
	Texture potion;
	Texture herb;
	Texture honey;
};

class Obstacle
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

	Obstacle(unsigned int);
	// move
	void move();
	// perform
	void perform();


	// get drawable Sprite
	Sprite getSprite() { return this->obstacle; };
	int getDamage() { return this->damage; };
	int getPoint() { return this->point; };
	int getGenCD() {
		return this->obstacle.getGlobalBounds().width / speedx + 1;
	};
	int getInterval() { return this->interval; };
private:
	bool loadTexture(Type);
	void setAttribute(Type);
	void usePotion();
	void useHerb();
	void useHoney();

	Type type;
	Sprite obstacle;
	Obstacle_texture texture;
	float speedx;
	int damage = 0;
	int point = 0;
	// time counter for item effect
	int interval = 0;
	// whether item effect is affect
	bool onEffect = false;
};
