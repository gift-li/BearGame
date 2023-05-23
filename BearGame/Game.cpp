#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Character.h"

using namespace sf;
using namespace std;

Game::Game()
{
	window.create(VideoMode(1440, 540), "Bear Game");

	mCharacter = new Character(Character::Bear);

	/*
	Font font;
	if (font.loadFromFile("font/ProbetaLightitalic-RpoaW.otf"))
	{
		// fail loading
		HPcounter.setFont(font);
	}
	HPcounter.setPosition(720, 270);
	HPcounter.setFillColor(Color::Red);
	HPcounter.setCharacterSize(30);
	*/
}

void Game::run()
{
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

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
	if (timer > delay)
	{
		if (genCD > 0)
		{
			genCD--;
		}
		else if (genCD == 0)
		{
			generateObstacle();
		}

		updateObstacle();

		updateHPcounter();

		timer = 0;
	}
}

void Game::generateObstacle()
{
	const bool pass = (rand() % genProb <= 1);
	if (pass)
	{
		Obstacle* newObs = new Obstacle(window.getSize().x);
		genCD = newObs->getGenCD();

		mObstacle.push_back(newObs);
	}
}

void Game::updateObstacle()
{
	vector<Obstacle*> aliveObstacle;

	for (auto& obstacle : mObstacle)
	{
		obstacle->move();

		if (obstacle->getSprite().getPosition().x >= 0)
		{
			aliveObstacle.push_back(obstacle);
		}
	}

	mObstacle = aliveObstacle;
}

void Game::updateHPcounter()
{
	// const int HP = mCharacter->getHP();
	HPcounter.setString("3");
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
	for (Obstacle* obstacle : mObstacle)
	{
		window.draw(obstacle->getSprite());
	}

	// draw HPcounter
	// window.draw(HPcounter);
	
	window.display();
}