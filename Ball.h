#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum EnemyBallTypes
{
	DEFAULT = 0,
	DAMAGE,
	HEALING,
	NROFTYPES
};

class Ball
{
private:

	sf::CircleShape				_shapeEnemy;
	int							_type;

	void						initShape(const sf::RenderWindow* window);

public:
	Ball();
	Ball(const sf::RenderWindow* window, int type);

	virtual ~Ball();

	// Accessor
	const sf::CircleShape&		getShape() const;
	const int&					getType() const;

												// Function
	void						update();
	void						render(sf::RenderTarget* target);

};

