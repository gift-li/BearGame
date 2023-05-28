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

	// get drawable Sprite
	Sprite getSprite();

	int getDamage();

	int getGenCD();
	// move
	void move();
private:
	bool loadTexture(Type);
	void setAttribute(Type);

	Sprite obstacle;
	Obstacle_texture texture;
	float speedx;
	int damage;
};
