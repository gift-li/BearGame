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
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		watchEvent();
		if (gameOn)
		{
			checkCollision();
			doSchedule();
			update();
			render();
		}
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
		mCharacter->idle();

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
	else if (Keyboard::isKeyPressed(Keyboard::R))
	{
		restart();
	}
}

void Game::releaseInput()
{
	mCharacter->resetMove();
}

void Game::updateCharacter()
{
	if (mCharacter->getStatus() == Character::IDLE)
	{
		mCharacter->idleMove();
	}
	else if (mCharacter->getStatus() == Character::JUMP)
	{
		mCharacter->jumpMove();
	}
	else if (mCharacter->getStatus() == Character::SQUAT)
	{
		mCharacter->squatMove();
	}
}

void Game::checkCollision()
{
	vector<Obstacle*> aliveObstacle;
	for (Obstacle* obstacle : mObstacle)
	{
		if(mCharacter->collide(obstacle->getSprite()))
		{
			if (mCharacter->checkInvincible() != true)
			{
				mCharacter->changeHP(obstacle->getDamage());
			}
			this->score += obstacle->getPoint();
			if (scheduleObstacle == nullptr) {
				// instantly change to new collide obstacle perform
				scheduleObstacle = obstacle;
			}
		}
		else
		{
			aliveObstacle.push_back(obstacle);
		}
	}
	// update mObstacle to alive obstacle
	this->mObstacle = aliveObstacle;
	aliveObstacle.clear();
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

		updateCharacter();

		updateObstacle();

		updateTextHP();
		updateTextScore();

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
	_textHP.setPosition(window.getSize().x / 2, 0);
	_textHP.setFont(font);
	_textHP.setCharacterSize(30);
	_textHP.setFillColor(Color::Red);
	// assign
	textHP = _textHP;

	Text _textScore;
	// setting
	_textScore.setPosition(window.getSize().x * 0.05, 0);
	_textScore.setFont(font);
	_textScore.setCharacterSize(30);
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
		textHP.setString("You lose!\nPress R to restart!");
		const float x = (window.getSize().x - textHP.getLocalBounds().width) / 2;
		textHP.setPosition(x, 0);
		gameOn = false;
	}
}

void Game::updateTextScore()
{
	textScore.setString(to_string(score));
}

void Game::doSchedule()
{
	if (scheduleObstacle != nullptr)
	{
		scheduleObstacle->perform();
		if (scheduleObstacle->getInterval() == 0)
		{
			this->scheduleObstacle = nullptr;
		}
	}
}

void Game::render()
{
	window.clear(Color::White);

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

	// draw text
	window.draw(textHP);
	window.draw(textScore);
	
	window.display();
}

void Game::restart()
{
	mCharacter->reset();
	mObstacle.clear();
	scheduleObstacle = nullptr;

	this->genCD = 0;
	this->score = 0;

	const float x = (window.getSize().x) / 2;
	this->textHP.setString(to_string(mCharacter->getHP()));
	this->textHP.setPosition(x, 0);

	this->textScore.setString(to_string(this->score));

	this->gameOn = true;
}