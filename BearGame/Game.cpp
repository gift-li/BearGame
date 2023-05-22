#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Character.h"

using namespace sf;
using namespace std;

Game::Game()
{
	// Game class constructor
	window.create(VideoMode(1440, 540), "Bear Game");
	mCharacter = new Character(Character::Bear);
}

void Game::run()
{
	int time = 0;
	int last_time = 0;

	while (window.isOpen()) {
		last_time = time;
		time = clock.getElapsedTime().asSeconds();

		watchEvent();

		checkCollision();

		update();

		render();
	}
}

void Game::watchEvent()
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::KeyPressed:
			pressInput();
			break;
		case Event::KeyReleased:
			releaseInput();
			break;
		case Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::pressInput()
{
	// trigger event when status is IDLE
	if (mCharacter->getStatus() == Character::IDLE)
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			mCharacter->jump();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			mCharacter->squat();
		}
	}
	// trigger props-cast event
	else if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		// do something
	}
}

void Game::releaseInput()
{
	// set Character status as IDLE
	mCharacter->idle();
}

void Game::checkCollision()
{
	vector<Obstacle*> aliveObstacle;

	for (Obstacle* obstacle : mObstacle)
	{
		if(mCharacter->collide(obstacle->getSprite()))
		{
			mCharacter->hit();
		}
		else
		{
			aliveObstacle.push_back(obstacle);
		}
	}
	// update mObstacle to alive obstacle
	this->mObstacle = aliveObstacle;
}

void Game::update()
{
	// update objects status
}

void Game::render()
{
	window.clear(Color::White);

	// get objects to display

	// Draw the line
	RectangleShape line(Vector2f(window.getSize().x, 2));
	line.setFillColor(Color::Black);
	line.setPosition(0, 390);
	window.draw(line);

	// draw Character
	window.draw(mCharacter->getSprite());

	// draw Obstacles
	/*
	for (Obstacle* obstacle : mObstacle)
	{
		window.draw(obstacle->getSprite());
	}
	*/
	
	window.display();
}