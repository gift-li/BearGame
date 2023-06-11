#include "Object.h"
#include "Tree.h"

using namespace sf;
using namespace std;

Tree::Tree()
{
	if (this->texture.loadFromFile("image/tree.png"))
	{
		setAttribute();
	}
}

void Tree::setAttribute()
{
	this->type = Object::TREE;
	this->damage = 1;
	this->point = 20;
	this->speedx = rand() % 15 + 35;

	this->sprite.setTexture(this->texture);
	this->scale = Vector2f(.15f, .15f);
	this->sprite.setScale(this->scale);
	this->sprite.setPosition(this->window_width, 340);
}