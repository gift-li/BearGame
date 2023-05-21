#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace sf;

Game::Game()
{
	// Game class constructor
	window.create(VideoMode(1440, 720), "Bear Game");
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
			proccessInput();
			break;
		case Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::proccessInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		// do something
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		// do something
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		// do something
	}
}

void Game::checkCollision()
{
	/*
	for (auto& obstacle : mObstacle)
	{
		if (mCharacter.collide(obstacle))
		{
			doSomething();
		}
	}
	*/
}

void Game::update()
{
	// update objects status
}

void Game::render()
{
	window.clear();

	// get objects to display

	// draw objects
	// window.draw();
	
	window.display();
}