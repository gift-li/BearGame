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
		/*
		TREE,
		EAGLE,
		GIANT_POTION,
		*/
		HERB,
		HONEY,

		// Don't remove: add enum entity above
		LAST
	};

	Obstacle(unsigned int);

	// get drawable Sprite
	Sprite getSprite();

	int getGenCD();
	// move
	void move();
private:
	bool loadTexture(Type);
	void setTexture(Type);
	void setScale(Type);

	Sprite obstacle;
	Obstacle_texture texture;
	float speedx;
};
