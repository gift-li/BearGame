#include "Game.h"
#include "Object.h"
#include "Potion.h"

using namespace sf;
using namespace std;

Potion::Potion()
{
	if (this->texture.loadFromFile("image/potion.png"))
	{
		setAttribute();
	}
}

void Potion::setAttribute()
{
	this->type = Object::POTION;
	this->interval = 3000;
	this->speedx = rand() % 15 + 20;

	this->sprite.setTexture(this->texture);
	this->scale = Vector2f(.25f, .25f);

	// Set the y-coordinate within the desired range
	int y = rand() % (320 - 160 + 1) + 160;

	this->sprite.setScale(this->scale);
	this->sprite.setPosition(
		this->window_width,
		y
	);
}

void Potion::perform()
{
	if (this->isTrigger)
	{
		this->interval--;
		return;
	}

	Game::getInstance().getCharacter()->setInvincible(true);
	Game::getInstance().getCharacter()->resize(Vector2f(2.f, 2.f));
	this->isTrigger = true;
}

void Potion::restore()
{
	Game::getInstance().getCharacter()->setInvincible(false);
	Game::getInstance().getCharacter()->resize(Vector2f(.5f, .5f));
}