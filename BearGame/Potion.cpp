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

void Potion::perform()
{
	/*
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
	*/
}