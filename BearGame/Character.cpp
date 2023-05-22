#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"

using namespace sf;
using namespace std;

Character::Character(Type type)
{
	if (loadTexture(type))
	{
		setTexture(type);
		cout << "Load character texture success" << endl;
	}
}

bool Character::collide(Sprite obstacle)
{
	return (character.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
		? true
		: false;
}

void Character::hit()
{
	if (this->HP >= 0)
	{
		this->reduceHP();
	}
}

void Character::jump()
{
	status = Character::JUMP;
	// move Character Y-axis
	// if not reach jump height: add Y-axis
	//	else: minus Y-axis
	// when reach ground: status == idle

	// character.move(Vector2f());
}

void Character::squat()
{
	status = Character::SQUAT;
	// move Character Y-axis
	// character.move(Vector2f());
}

void Character::idle()
{
	status = Character::IDLE;
}

Character::Status Character::getStatus()
{
	return this->status;
}

Sprite Character::getSprite()
{
	return this->character;
}

bool Character::loadTexture(Type type)
{
	switch (type)
	{
	case Character::Bear:
		return (!texture.bear.loadFromFile("bear.jpg"))
			? false
			: true;
	default:
		cout << "Invalid Character loadTexture" << endl;
		return false;
	}
}

void Character::setTexture(Type type)
{
	switch (type)
	{
	case Character::Bear:
		character.setTexture(texture.bear);
		break;
	default:
		cout << "Invalid Character setTexture" << endl;
		break;
	}
}

void Character::reduceHP()
{
	this->HP--;
}