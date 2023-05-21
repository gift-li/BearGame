#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Obstacle.h"
#include "enum.h"

using namespace sf;
using namespace std;

Obstacle::Obstacle()
{
	if (!LoadTexture())
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

	return this->obstacle;
}

Sprite Obstacle::generate(Type type)
{
	setScale(type);
	setTexture(type);

	return this->obstacle;
}

void Obstacle::setTexture(Type type)
{
	switch (type)
	{
	case Obstacle::TREE:
		this->obstacle.setTexture(this->custom_texture.eagle);
		break;
	case Obstacle::EAGLE:
		this->obstacle.setTexture(this->custom_texture.tree);
		break;
	case Obstacle::GIANT_POTION:
		this->obstacle.setTexture(this->custom_texture.giant_potion);
		break;
	case Obstacle::MAGIC_HERB:
		this->obstacle.setTexture(this->custom_texture.magic_herb);
		break;
	case Obstacle::INVINCIBLE_HONEY:
		this->obstacle.setTexture(this->custom_texture.invincible_honey);
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
		this->obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::EAGLE:
		this->obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::GIANT_POTION:
		this->obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::MAGIC_HERB:
		this->obstacle.setScale(1.f, 1.f);
		break;
	case Obstacle::INVINCIBLE_HONEY:
		this->obstacle.setScale(1.f, 1.f);
		break;
	default:
		cout << "Invalid obstacle setScale" << endl;
		break;
	}
}

Sprite Obstacle::getSprite()
{
	return this->obstacle;
}

bool Obstacle::LoadTexture()
{
	if (!this->custom_texture.tree.loadFromFile("tree.jpg"))
		return EXIT_FAILURE;
	if (!this->custom_texture.eagle.loadFromFile("eagle.jpg"))
		return EXIT_FAILURE;
	if (!this->custom_texture.giant_potion.loadFromFile("giant_potion.jpg"))
		return EXIT_FAILURE;
	if (!this->custom_texture.magic_herb.loadFromFile("magic_herb.jpg"))
		return EXIT_FAILURE;
	if (!this->custom_texture.invincible_honey.loadFromFile("invincible_honey.jpg"))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}