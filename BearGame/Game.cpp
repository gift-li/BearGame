#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Character.h"

using namespace sf;
using namespace std;

Game::Game()
{
	if (!font.loadFromFile("font/PIXEAB__.TTF"))
	{
		// fail loading
		cout << "Fail loading font" << endl;
	}
	window.create(VideoMode(1440, 540), "Bear Game");
	mCharacter = new Character(Character::Bear);
	initText();
}

void Game::run()
{
	while (window.isOpen()) {
		if (gameOn)
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
		}

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
	if (timer > delay && gameOn)
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

		updateTextHP();
		// updateTextScore();

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

void Game::initText()
{
	Text _textHP;
	// setting
	_textHP.setPosition(window.getSize().x/2, 0);
	_textHP.setFont(font);
	_textHP.setCharacterSize(40);
	_textHP.setFillColor(Color::Red);
	// assign
	textHP = _textHP;

	Text _textScore;
	// setting
	_textScore.setPosition(window.getSize().x * 0.8, 0);
	_textScore.setFont(font);
	_textScore.setCharacterSize(40);
	_textScore.setFillColor(Color::Black);
	// assign
	textScore = _textScore;
}

void Game::updateTextHP()
{
	const int HP = mCharacter->getHP();
	if (HP > 0)
	{
		textHP.setString(to_string(HP));
	}
	else
	{
		textHP.setString("You lose!");
		const float x = (window.getSize().x - textHP.getLocalBounds().width) / 2;
		textHP.setPosition(x, 0);
		gameOn = false;
	}
}

void Game::updateTextScore()
{

}

void Game::render()
{
	window.clear(Color::White);

	// get objects to display

	// Draw the line
	RectangleShape line(Vector2f(window.getSize().x, 2));
	line.setFillColor(Color::Black);
	line.setPosition(0, 450);
	window.draw(line);

	// draw Character
	window.draw(mCharacter->getSprite());

	// draw Obstacles
	for (Obstacle* obstacle : mObstacle)
	{
		window.draw(obstacle->getSprite());
	}

	// draw textHP
	window.draw(textHP);
	// window.draw(textScore);
	
	window.display();
}