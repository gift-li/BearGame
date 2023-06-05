#include "Object.h"
#include "Eagle.h"

using namespace sf;
using namespace std;

Eagle::Eagle()
{
	if (this->texture.loadFromFile("image/eagle.png"))
	{
		setAttribute();
	}
}

void Eagle::setAttribute()
{
	this->type = Object::EAGLE;
	this->damage = 1;
	this->speedx = rand() % 15 + 20;

	this->sprite.setTexture(this->texture);
	this->scale = Vector2f(.15f, .15f);
	this->sprite.setScale(this->scale);
	this->sprite.setPosition(
		this->window_width,
		rand() % (int)(435 - this->sprite.getGlobalBounds().height));
}