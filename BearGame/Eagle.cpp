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
    this->point = 20;
    this->speedx = rand() % 15 + 35;

    this->sprite.setTexture(this->texture);
    this->scale = Vector2f(.15f, .15f);
    this->sprite.setScale(this->scale);

    float yCoordinate = 200.0f;
    int randomValue = rand() % 2;

    switch (randomValue)
    {
    case 0:
        yCoordinate = 60.0f;
        isLow = false;
        break;
    case 1:
        yCoordinate = 225.0f;
        isLow = true;
        break;
    }
    this->sprite.setPosition(
        this->window_width,
        yCoordinate);
}
