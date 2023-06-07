#include <iostream>
#include "Game.h"
#include "Object.h"
#include "Honey.h"

using namespace sf;
using namespace std;

Honey::Honey()
{
	if (this->texture.loadFromFile("image/honey.png"))
	{
		setAttribute();
	}
}

void Honey::setAttribute()
{
	this->type = Object::HONEY;
	this->point = 20;
	this->interval = 3000;
	this->speedx = rand() % 15 + 20;

	this->sprite.setTexture(this->texture);
	this->scale = Vector2f(.25f, .25f);
	this->sprite.setScale(this->scale);
	this->sprite.setPosition(
		this->window_width,
		rand() % (int)(435 - this->sprite.getGlobalBounds().height));
}

void Honey::perform()
{
	if (this->isTrigger)
	{
		this->interval--;
		return;
	}

	Game::getInstance().getCharacter()->setInvincible(true);
	this->isTrigger = true;
}

void Honey::restore()
{
	Game::getInstance().getCharacter()->setInvincible(false);
}