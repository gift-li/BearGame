#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Obstacle texture (image)
struct Obstacle_texture
{
	Texture tree;
	Texture eagle;
	Texture giant_potion;
	Texture magic_herb;
	Texture invincible_honey;
};

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

		// Don't remove: add enum entity above
		LAST
	};

	Obstacle();

	// generate Obstacle randomly
	Sprite generate();
	// generate Obstacle with required props
	Sprite generate(Type);
	// get drawable Sprite
	Sprite getSprite();
private:
	bool loadTexture();
	void setTexture(Type);
	void setScale(Type);

	Sprite obstacle;
	Obstacle_texture texture;
};
