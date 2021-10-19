#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Ball.h"

class Game
{
private:

	sf::VideoMode			_videoMode;
	sf::RenderWindow*		_window;
	sf::Event				_sfmlEvent;
	bool					_endGame;

															// Player
	Player					_player;

	int						_points;
															// Enemy
	std::vector<Ball>		_enemyBall;
	float					_spawnTimerMax;
	float					_spawnTimer;
	int						_maxBall;

															// Text style
	sf::Font				_font;
	sf::Text				_guiText;
	sf::Text				_textEndGame;

	void					initVariables();
	void					initWindow();
	void					initFonts();
	void					initText();

public:
															// Constructor
	Game();

															// Destructor
	virtual ~Game();

															// Accessors
	const bool&				getEndGame() const;

															// Modifiers

															// Functions
	const bool				running() const;
	const int				randBallType() const;
	void					updatePlayer();
	void					pollEvents();

	void					spawnBalls();
	void					updateCollision();
	void					updateGui();
	void					update();

	void					renderGui(sf::RenderTarget* target);
	void					render();
		
};

