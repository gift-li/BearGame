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
	this->interval = 2000;
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
	/*
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
	*/
}