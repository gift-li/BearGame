#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Obstacle
{
public:
	enum Type
	{
		TREE,
		EAGLE,
		GIANT_POTION,
		MAGIC_HERB,
		INVINCIBLE_HONEY,

		// Don't remove: add entity above
		LAST
	};

	Obstacle();

	Sprite generate();
	Sprite generate(Type);

	Sprite getSprite();
private:
	bool LoadTexture();
	void setTexture(Type);
	void setScale(Type);

	Sprite obstacle;
	custom_texture custom_texture;
};

// Obstacle texture (image)
struct custom_texture
{
	Texture tree;
	Texture eagle;
	Texture giant_potion;
	Texture magic_herb;
	Texture invincible_honey;
};
