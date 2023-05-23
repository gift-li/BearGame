#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Obstacle.h"

using namespace sf;
using namespace std;

Obstacle::Obstacle(unsigned int window_width)
{
	srand((unsigned)time(NULL));
	Type rand_type = Type(rand() % Obstacle::LAST);

	if (loadTexture(rand_type))
	{
		// random generate obstacle
		setTexture(rand_type);
		setScale(rand_type);
		speedx = rand() % 10 + 10;
		obstacle.setPosition(Vector2f(window_width, rand() % 230));

		cout << "Build Obstacle success" << endl;
	}
}

void Obstacle::setTexture(Type type)
{
	switch (type)
	{
		/*
	case Obstacle::TREE:
		obstacle.setTexture(texture.eagle);
		break;
	case Obstacle::EAGLE:
		obstacle.setTexture(texture.tree);
		break;
	case Obstacle::GIANT_POTION:
		obstacle.setTexture(texture.potion);
		break;
		*/
	case Obstacle::HERB:
		obstacle.setTexture(texture.herb);
		break;
	case Obstacle::HONEY:
		obstacle.setTexture(texture.honey);
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
		/*
	case Obstacle::TREE:
		obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::EAGLE:
		obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::POTION:
		obstacle.setScale(1.f, 1.f);
		break;
		*/
	case Obstacle::HERB:
		obstacle.setScale(.3f, .3f);
		break;
	case Obstacle::HONEY:
		obstacle.setScale(.3f, .3f);
		break;
	default:
		cout << "Invalid obstacle setScale" << endl;
		break;
	}
}

void Obstacle::move()
{
	obstacle.move(Vector2f(-speedx, 0));
}

Sprite Obstacle::getSprite()
{
	return this->obstacle;
}

int Obstacle::getGenCD()
{
	return obstacle.getGlobalBounds().width / speedx + 1;
}

bool Obstacle::loadTexture(Type type)
{
	/*
	if (!texture.tree.loadFromFile("tree.jpg"))
		return EXIT_FAILURE;
	if (!texture.eagle.loadFromFile("eagle.jpg"))
		return EXIT_FAILURE;
	if (!texture.giant_potion.loadFromFile("giant_potion.jpg"))
		return EXIT_FAILURE;
	*/
	switch (type)
	{
	case Obstacle::HERB:
		return texture.herb.loadFromFile("image/herb.png");
	case Obstacle::HONEY:
		return texture.honey.loadFromFile("image/honey.png");
	default:
		cout << "Invalid Obstacle loadTexture" << endl;
		return false;
	}
}