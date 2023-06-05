#include "Object.h"
#include "Herb.h"

using namespace sf;
using namespace std;

Herb::Herb()
{
	if (this->texture.loadFromFile("image/herb.png"))
	{
		setAttribute();
	}
}

void Herb::setAttribute()
{
	this->type = Object::HERB;
	this->point = 20;
	this->speedx = rand() % 15 + 20;

	this->sprite.setTexture(this->texture);
	this->scale = Vector2f(.25f, .25f);
	this->sprite.setScale(this->scale);
	this->sprite.setPosition(
		this->window_width,
		rand() % (int)(435 - this->sprite.getGlobalBounds().height));
}

void Herb::perform()
{
	/*
	vector<Obstacle*> obs = Game::getInstance().getObstacle();
	obs.erase(obs.begin());
	*/
}