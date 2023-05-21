#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Obstacle.h"

using namespace sf;
using namespace std;

Obstacle::Obstacle()
{
	if (!loadTexture())
	{
		cout << "Load texture success" << endl;
	}

	srand((unsigned)time(NULL));
}

Sprite Obstacle::generate()
{
	// random generate obstacle
	Type rand_type = Type(rand() % Obstacle::LAST);

	generate(rand_type);

	return obstacle;
}

Sprite Obstacle::generate(Type type)
{
	setScale(type);
	setTexture(type);

	return obstacle;
}

void Obstacle::setTexture(Type type)
{
	switch (type)
	{
	case Obstacle::TREE:
		obstacle.setTexture(texture.eagle);
		break;
	case Obstacle::EAGLE:
		obstacle.setTexture(texture.tree);
		break;
	case Obstacle::GIANT_POTION:
		obstacle.setTexture(texture.giant_potion);
		break;
	case Obstacle::MAGIC_HERB:
		obstacle.setTexture(texture.magic_herb);
		break;
	case Obstacle::INVINCIBLE_HONEY:
		obstacle.setTexture(texture.invincible_honey);
		break;
	default:
		cout << "Invalid obstacle setTexture" << endl;
		break;
	}
}

void Obstacle::setScale(Type type)
{
	switch (type)
	{
	case Obstacle::TREE:
		obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::EAGLE:
		obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::GIANT_POTION:
		obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::MAGIC_HERB:
		obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::INVINCIBLE_HONEY:
		obstacle.setScale(1.f, 1.f);
		break;
	default:
		cout << "Invalid obstacle setScale" << endl;
		break;
	}
}

Sprite Obstacle::getSprite()
{
	return obstacle;
}

bool Obstacle::loadTexture()
{
	if (!texture.tree.loadFromFile("tree.jpg"))
		return EXIT_FAILURE;
	if (!texture.eagle.loadFromFile("eagle.jpg"))
		return EXIT_FAILURE;
	if (!texture.giant_potion.loadFromFile("giant_potion.jpg"))
		return EXIT_FAILURE;
	if (!texture.magic_herb.loadFromFile("magic_herb.jpg"))
		return EXIT_FAILURE;
	if (!texture.invincible_honey.loadFromFile("invincible_honey.jpg"))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}