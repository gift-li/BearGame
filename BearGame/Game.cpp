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
	while (window.isOpen()) {

		watchEvent();

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