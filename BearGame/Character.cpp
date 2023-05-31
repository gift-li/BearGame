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
	
	HP = 3;
}

void Character::reset()
{
	this->HP = 3;
	this->jumpHeight = 0;
	this->jumpSpeed = 0;
	this->g = 0;
	character.setPosition(sf::Vector2f(120.f, 330.f));
}

bool Character::collide(Sprite obstacle)
{
	return character.getGlobalBounds().intersects(obstacle.getGlobalBounds());
}

void Character::jump()
{
	status = Character::JUMP;
	this->jumpHeight = 150.f;
	this->jumpSpeed = 60.f;
	this->g = 10.f;
}

void Character::move()
{
	character.move(Vector2f(0,-jumpSpeed));
	jumpSpeed = jumpSpeed - g;
	Vector2f position = character.getPosition();
	if (position.y >= 330.0f)
	{
		//character.setPosition(Vector2f(120.f, 330.f));
		status = Character::IDLE;
	}
}

void Character::squat()
{
	status = Character::SQUAT;
	// move Character Y-axis
	// character.move(Vector2f());
}

bool Character::loadTexture(Type type)
{
	switch (type)
	{
	case Character::Bear:
		return texture.bear.loadFromFile("Image/bear_jump.png");
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
		character.setScale(0.3f, 0.3f);
		character.setPosition(sf::Vector2f(120.f, 330.f));
		break;
	default:
		cout << "Invalid Character setTexture" << endl;
		break;
	}
}