#pragma once
#include <SFML/Graphics.hpp>

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
	custom_texture texture;
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
