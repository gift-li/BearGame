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

	const float jumpHeight = 150.0f; // Height at which the character jumps
	const float jumpSpeed = 5.0f;    // Speed at which the character jumps
	const float gravity = 9.8f;      // Acceleration due to gravity

	Vector2f position = character.getPosition();
	float initialVelocity = sqrt(2 * gravity * jumpHeight);

	while (position.y >= 150.0f)
	{
		// Move character upwards
		position.y -= jumpSpeed;
		character.setPosition(position);

		// Calculate new velocity based on gravity
		initialVelocity -= gravity;

		// Delay to control the jump speed
		sf::sleep(sf::milliseconds(10));
	}

	while (position.y < 270.0f)
	{
		// Move character downwards
		position.y += jumpSpeed;
		character.setPosition(position);

		// Calculate new velocity based on gravity
		initialVelocity += gravity;

		// Delay to control the jump speed
		sf::sleep(sf::milliseconds(10));
	}

	// Set character position to ground level
	character.setPosition(position.x, 270.0f);

	status = Character::IDLE;
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
		return (!texture.bear.loadFromFile("Image/bear_jump.png"))
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
		character.setScale(0.3f, 0.3f);
		character.setPosition(sf::Vector2f(120.f, 270.f));
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