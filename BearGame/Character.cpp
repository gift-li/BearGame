#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"

using namespace sf;
using namespace std;

Character::Character()
{
	if (loadTexture())
	{
		setAttribute();
	}
}

void Character::reset()
{
	this->HP = 3;
	this->jumpHeight = 0;
	this->jumpSpeed = 0;
	this->g = 0;
	this->status = Character::IDLE;
	this->isInvincible = false;
	this->idleSwitch = true;
	this->baseX = 120.f;
	this->baseY = 330.f;
	if (loadTexture())
	{
		setAttribute();
	}
}

bool Character::collide(Sprite obstacle)
{
	return character.getGlobalBounds().intersects(obstacle.getGlobalBounds());
}

void Character::idle()
{
	status = Character::IDLE;
}

void Character::idleMove()
{
	cd--;
	if (cd == 0)
	{
		if (idleSwitch)
		{
			character.setTexture(texture.idle2);
			idleSwitch = false;
		}
		else 
		{
			character.setTexture(texture.idle1);
			idleSwitch = true;
		}
		cd = 5;
	}
}

void Character::jump()
{
	status = Character::JUMP;
	this->jumpHeight = 150.f;
	this->jumpSpeed = 60.f;
	this->g = 10.f;
}

void Character::jumpMove()
{
	character.setTexture(texture.jump);
	character.move(Vector2f(0, -jumpSpeed));
	jumpSpeed -= g;
	Vector2f position = character.getPosition();
	if (position.y >= baseY)
	{
		status = Character::IDLE;
		idleSwitch = true;
		character.setTexture(texture.idle1);
	}
}

void Character::squat()
{
	status = Character::SQUAT;
}

void Character::squatMove()
{
	character.setTexture(texture.squat);
}

void Character::resetMove()
{
	if (status != Character::JUMP)
	{
		status = Character::IDLE;
		character.setTexture(texture.idle2);
		idleSwitch = true;
	}
}

bool Character::changeHP(int offset)
{
	if (checkInvincible())
	{
		return false; 
	}
	else
	{
		this->HP -= offset;
		return true;
	}
}

void Character::resize(Vector2f _scale)
{
	if (loadTexture())
	{
		this->character.scale(_scale);
		const Vector2f currentPosition = this->character.getPosition();
		const float height = this->character.getGlobalBounds().height;
		if (_scale.x > 1 && _scale.y > 1)
		{
			this->character.setPosition(
				currentPosition.x,
				currentPosition.y - height / 2
			);
			this->baseY -= height / 2;
		}
		else
		{
			this->character.setPosition(
				currentPosition.x,
				currentPosition.y + height
			);
			this->baseY += height;
		}
	}
}

bool Character::loadTexture()
{
	return (texture.idle1.loadFromFile("Image/bear_idle1.png")
		&& texture.idle2.loadFromFile("Image/bear_idle2.png")
		&& texture.jump.loadFromFile("Image/bear_jump.png")
		&& texture.squat.loadFromFile("Image/bear_squat.png"));
}

void Character::setAttribute()
{
	character.setTexture(texture.idle1);
	character.setScale(0.3f, 0.3f);
	character.setPosition(baseX, baseY);
}