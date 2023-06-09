﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Object.h"

using namespace sf;
using namespace std;

Game::Game()
{
	srand(time(NULL));
	if (!font.loadFromFile("font/PIXEAB__.TTF"))
	{
		cout << "Fail loading font" << endl;
	}

	window.create(VideoMode(1440, 540), "Bear Game");
	mCharacter = new Character();
	initText();

	if (!explosionTexture.loadFromFile("Image/explosion.png"))
	{
		cout << "Failed to load explosion texture" << endl;
	}
}

void Game::drawStartScreen()
{
	window.clear(sf::Color::White);

	sf::Text startText;
	startText.setFont(font);
	startText.setString("BEAR GAME");
	startText.setCharacterSize(50);
	startText.setFillColor(sf::Color::Black);
	startText.setStyle(sf::Text::Bold);
	startText.setPosition(window.getSize().x / 2 - startText.getLocalBounds().width / 2,
		window.getSize().y / 2 - startText.getLocalBounds().height / 2);

	window.draw(startText);

	window.display();
}

void Game::run()
{
	while (window.isOpen()) {
		if (!gameStarted) {
			drawStartScreen();

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
					gameStarted = true;
					clock.restart();
				}
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
		}
		else {
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
	if (gameOn)
	{
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
	}

	if (Keyboard::isKeyPressed(Keyboard::R))
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
	vector<Object*> aliveObject;
	for (Object* object : mObject)
	{
		if (mCharacter->collide(object->getSprite()))
		{
			if (!mCharacter->checkInvincible()
				&& mCharacter->changeHP(object->getDamage())
				&& !object->getLow())
			{
				updateTextHP();
			}

			this->score += object->getPoint() * object->getRatio();
			updateTextScore();

			if (object->isItem() && mSchedule == nullptr) {
				// instantly change to new collide object perform
				mSchedule = object;
			}
		}
		else
		{
			aliveObject.push_back(object);
		}
	}
	// update mObject to alive object
	this->mObject = aliveObject;
	aliveObject.clear();
}

void Game::update()
{
	if (timer > delay)
	{
		// update objects status
		if (mObject.size() < MAX_OBJECT)
		{
			genObject();
		}

		updateCharacter();
		updateObject();
		timer = 0;
	}

	if (scoreTimer.getElapsedTime().asSeconds() >= 0.1)
	{
		this->score += 10;
		updateTextScore();
		printf("%i\n", score);
		scoreTimer.restart();
	}
}

void Game::genObject()
{
	const bool pass = (rand() % genProb <= 1);
	if (pass)
	{
		mObject.push_back(Object::random());
	}
}

void Game::updateObject()
{
	vector<Object*> aliveObject;
	for (auto& object : mObject)
	{
		if (!object->checkAlive()) { continue; };

		object->move();
		if (object->getSprite().getPosition().x >= 0)
		{
			aliveObject.push_back(object);
		}
	}

	mObject = aliveObject;
	aliveObject.clear();
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
	updateTextHP();

	Text _textScore;
	// setting
	_textScore.setPosition(window.getSize().x * 0.1, 0);
	_textScore.setFont(font);
	_textScore.setCharacterSize(30);
	_textScore.setFillColor(Color::Black);
	// assign
	textScore = _textScore;
	updateTextScore();
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
	if (mSchedule)
	{
		if (mSchedule->getInterval() > 0)
		{
			mSchedule->perform();
			return;
		}

		mSchedule->restore();
		mSchedule = NULL;
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

	// draw Object
	for (Object* object : mObject)
	{
		window.draw(object->getSprite());
	}

	// draw text
	window.draw(textHP);
	window.draw(textScore);
	
	window.display();
}

void Game::restart()
{
	mCharacter->reset();
	mObject.clear();
	mSchedule = nullptr;

	this->textHP.setPosition((window.getSize().x) / 2, 0);
	this->textHP.setString(to_string(mCharacter->getHP()));

	this->score = 0;
	this->textScore.setString(to_string(this->score));

	this->gameOn = true;
}

void Game::resizeCharacter(Vector2f scale)
{
	mCharacter->resize(scale);
}