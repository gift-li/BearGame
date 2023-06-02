#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Obstacle.h"
#include "Game.h"

using namespace sf;
using namespace std;

Obstacle::Obstacle(unsigned int window_width)
{
	// srand((unsigned)time(NULL));
	Type rand_type = Type(rand() % Obstacle::LAST);

	if (loadTexture(rand_type))
	{
		// random generate obstacle
		this->type = rand_type;
		setAttribute(rand_type);
		speedx = rand() % 15 + 20;
		obstacle.setPosition(
			window_width, 
			rand() % (int)(435 - this->obstacle.getGlobalBounds().height));
	}
}

void Obstacle::setAttribute(Type type)
{
	switch (type)
	{
	case Obstacle::TREE:
		obstacle.setTexture(texture.tree);
		obstacle.setScale(.15f, .15f);
		this->damage = 1;
		this->point = 20;
		break;
	case Obstacle::EAGLE:
		obstacle.setTexture(texture.eagle);
		obstacle.setScale(.15f, .15f);
		this->damage = 1;
		break;
	case Obstacle::POTION:
		obstacle.setTexture(texture.potion);
		obstacle.setScale(.25f, .25f);
		this->point = 20;
		this->interval = 2000;
		break;
	case Obstacle::HERB:
		obstacle.setTexture(texture.herb);
		obstacle.setScale(.25f, .25f);
		this->point = 20;
		break;
	case Obstacle::HONEY:
		obstacle.setTexture(texture.honey);
		obstacle.setScale(.25f, .25f);
		this->point = 20;
		this->interval = 2000;
		break;
	default:
		cout << "Invalid obstacle setAttribute" << endl;
		break;
	}
}

void Obstacle::move()
{
	obstacle.move(Vector2f(-speedx, 0));
}

void Obstacle::perform()
{
	switch (this->type)
	{
	case Obstacle::POTION:
		usePotion();
	case Obstacle::HERB:
		useHerb();
	case Obstacle::HONEY:
		useHoney();
	default:
		break;
	}
}

void Obstacle::useHerb()
{
	vector<Obstacle*> obs = Game::getInstance().getObstacle();
	obs.erase(obs.begin());
}

void Obstacle::useHoney()
{
	if (!this->onEffect)
	{
		Game::getInstance().getCharacter()->setInvincible(true);
		this->onEffect = true;
	}
	else
	{
		this->interval--;
		if (this->interval == 0)
		{
			Game::getInstance().getCharacter()->setInvincible(false);
			cout << Game::getInstance().getCharacter()->checkInvincible() << endl;
		}
	}
}

void Obstacle::usePotion()
{
	if (!this->onEffect)
	{
		Game::getInstance().getCharacter()->getSprite()
			.scale(1.f, 4.f);
		this->onEffect = true;
	}
	else
	{
		this->interval--;
		if (this->interval == 0)
		{
			Game::getInstance().getCharacter()->getSprite()
				.scale(1.f, .25f);
		}
	}
}

bool Obstacle::loadTexture(Type type)
{
	switch (type)
	{
	case Obstacle::TREE:
		return texture.tree.loadFromFile("image/tree.png");
	case Obstacle::EAGLE:
		return texture.eagle.loadFromFile("image/eagle.png");
	case Obstacle::POTION:
		return texture.potion.loadFromFile("image/potion.png");
	case Obstacle::HERB:
		return texture.herb.loadFromFile("image/herb.png");
	case Obstacle::HONEY:
		return texture.honey.loadFromFile("image/honey.png");
	default:
		cout << "Invalid Obstacle loadTexture" << endl;
		return false;
	}
}