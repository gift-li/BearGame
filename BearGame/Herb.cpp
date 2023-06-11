#include "Game.h"
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
    this->speedx = rand() % 15 + 20;
    this->point = 0;

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


void Herb::perform()
{
	if (Game::getInstance().getObject().size() > 0)
	{
		Game::getInstance().getObject().front()->setAlive(false);
	}
	this->interval--;
}