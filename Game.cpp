#include "Game.h"

void Game::initVariables()
{
	_endGame		= false;
	_spawnTimerMax	= 10.f;
	_spawnTimer		= _spawnTimerMax;
	_maxBall		= 10;
	_points			= 0;
}

void Game::initWindow()
{
	_videoMode		= sf::VideoMode(800, 600);
	_window			= new sf::RenderWindow(_videoMode, "Col Game", sf::Style::Default);
	_window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!_font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS - COULD NOT LOAD FILE" << std::endl;
	}
}

void Game::initText()
{
												// Count point & health
	_guiText.setFont(_font);
	_guiText.setFillColor(sf::Color::White);
	_guiText.setCharacterSize(24);

												// Text when the game is END
	_textEndGame.setFont(_font);
	_textEndGame.setFillColor(sf::Color::Red);
	_textEndGame.setCharacterSize(60);
	_textEndGame.setPosition(sf::Vector2f(280, 250));
	_textEndGame.setString("END GAME");
}

												// Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

												// Destructor
Game::~Game()
{
	delete _window;
}

const bool & Game::getEndGame() const
{
	return _endGame;
}

const bool Game::running() const
{
	return _window->isOpen();
}

const int Game::randBallType() const
{
	int type = EnemyBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
	{
		type = EnemyBallTypes::DAMAGE;
	}
	else if (randValue > 80 && randValue <= 100)
	{
		type = EnemyBallTypes::HEALING;
	}

	return type;
}

void Game::updatePlayer()
{
	_player.update(_window);					// Player::update()

	if (_player.getHp() <= 0)
	{
		_endGame = true;
	}
}

void Game::pollEvents()
{
	while (_window->pollEvent(_sfmlEvent))
	{
		switch (_sfmlEvent.type)
		{
			case sf::Event::Closed:
				_window->close();
				break;
			case sf::Event::KeyPressed:
				if (_sfmlEvent.key.code == sf::Keyboard::Escape)
					_window->close();
				break;
		}
	}
}

void Game::spawnBalls()
{
												// Timer
	if (_spawnTimer < _spawnTimerMax)
	{
		_spawnTimer += 1.f;
	}
	else
	{
		if (_enemyBall.size() < _maxBall)
		{
			_enemyBall.push_back(Ball(_window, this->randBallType()));

			_spawnTimer = 0.f;
		}
	}
}

void Game::updateCollision()
{

												// Check the collision
	for (size_t i = 0; i < _enemyBall.size(); i++)
	{
		if (_player.getShape().getGlobalBounds().intersects(_enemyBall[i].getShape().getGlobalBounds()))
		{
			switch (_enemyBall[i].getType())
			{
			case EnemyBallTypes::DEFAULT:
				_points++;
				break;
			case EnemyBallTypes::DAMAGE:
				_player.makeDamage(5);
				break;
			case EnemyBallTypes::HEALING:
				_player.gainHealth(2);
				break;
			}

												// Remove the ball
			_enemyBall.erase(_enemyBall.begin() + i); 
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << " POINTS: " << _points << std::endl
		<< " HEALTH: " << _player.getHp() << "/"
		<< _player.getHpMax();

	_guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (_endGame == false)
	{
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(_guiText);
}

void Game::render()
{
	_window->clear();

												// Render stuff
												// Render Player::render()
	_player.render(_window);

												// Render enemy balls
	for (auto i : _enemyBall)
	{
		i.render(_window);
	}

												// Render END text
	if (_endGame == true)
	{
		_window->draw(_textEndGame);
	}
	
												// Render gui
	this->renderGui(_window);
	_window->display();
}