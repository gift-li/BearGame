#include <SFML/Graphics.hpp>
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

	/*
	if (!explosionTexture.loadFromFile("Image/explosion.png"))
	{
		cout << "Failed to load explosion texture" << endl;
	}
	*/
}

void Game::drawStartScreen()
{
	window.clear(Color::White);

	Text startText;
	startText.setFont(font);
	startText.setString("BEAR GAME\nPress space to start");
	startText.setCharacterSize(50);
	startText.setFillColor(Color::Black);
	startText.setStyle(Text::Bold);
	startText.setPosition(
		window.getSize().x / 2 - startText.getLocalBounds().width / 2,
		window.getSize().y / 2 - startText.getLocalBounds().height / 2
	);

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
	if (gameOn && mCharacter->getStatus() == Character::IDLE)
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
			if (!mCharacter->checkInvincible())
			{
				if (object->checkLow())
				{
					if (mCharacter->getStatus() != Character::SQUAT)
					{
						if (mCharacter->changeHP(object->getDamage())) {
							updateTextHP();
						}
					}
				}
				else
				{
					if (mCharacter->changeHP(object->getDamage())) {
						updateTextHP();
					}
				}
			}

			this->objectScore += object->getPoint() * object->getRatio();
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
		if (genCD == 0)
		{
			genObject();
		}
		else
		{
			genCD--;
		}

		updateCharacter();
		updateObject();
		timer = 0;
	}

	if (scoreTimer.getElapsedTime().asSeconds() >= 0.1)
	{
		this->timeScore += 10;
		updateTextScore();
		scoreTimer.restart();
	}
}

void Game::genObject()
{
	const bool pass = (rand() % genProb <= 1);
	if (pass)
	{
		mObject.push_back(Object::random());
		genCD = GEN_CD;
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

	Text _textInvincible;
	_textInvincible.setPosition(window.getSize().x / 2, 50);
	_textInvincible.setFont(font);
	_textInvincible.setCharacterSize(30);
	_textInvincible.setFillColor(Color::Green);
	textInvincible = _textInvincible;
	updateTextInvincible();
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
		textHP.setString("You lose!\nPress R to restart!\nScore: " + to_string(objectScore+timeScore+20));
		const float x = (window.getSize().x - textHP.getLocalBounds().width) / 2;
		textHP.setPosition(x, 0);
		gameOn = false;
	}
}

void Game::updateTextScore()
{
	textScore.setString(to_string(objectScore)+" + " + to_string(timeScore));
}

void Game::updateTextInvincible()
{
	if (mCharacter->checkInvincible())
	{
		textInvincible.setString("~!! Invincible !!~");
	}
	else
	{
		textInvincible.setString("");
	}
	const float x = (window.getSize().x - textInvincible.getLocalBounds().width) / 2;
	textInvincible.setPosition(x, 50);
}

void Game::doSchedule()
{
	if (mSchedule)
	{
		if (mSchedule->getInterval() > 0)
		{
			mSchedule->perform();
			updateTextInvincible();
			return;
		}

		mSchedule->restore();
		mSchedule = NULL;
		updateTextInvincible();
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
	if (gameOn)
	{
		window.draw(textInvincible);
	}
	
	window.display();
}

void Game::restart()
{
	mCharacter->reset();
	mObject.clear();
	mSchedule = nullptr;

	this->textHP.setPosition((window.getSize().x) / 2, 0);
	this->textHP.setString(to_string(mCharacter->getHP()));

	this->timeScore = 0;
	this->objectScore = 0;
	this->textScore.setString(to_string(objectScore) + " + " + to_string(timeScore));
	updateTextInvincible();

	this->gameOn = true;
}