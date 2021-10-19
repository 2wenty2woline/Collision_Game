#include "Ball.h"

void Ball::initShape(const sf::RenderWindow* window)
{
	_shapeEnemy.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color color;
	switch (_type)
	{
	case DEFAULT:
		color		= sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGE:
		color		= sf::Color::Red;
		_shapeEnemy.setOutlineColor(sf::Color::White);
		_shapeEnemy.setOutlineThickness(2.f);
		break;
	case HEALING:
		color		= sf::Color::Green;
		_shapeEnemy.setOutlineColor(sf::Color::White);
		_shapeEnemy.setOutlineThickness(2.f);
		break;
	}
	
	_shapeEnemy.setFillColor(color);
	_shapeEnemy.setPosition(sf::Vector2f(static_cast<float>(rand() % window->getSize().x - _shapeEnemy.getGlobalBounds().width),
										 static_cast<float>(rand() % window->getSize().y - _shapeEnemy.getGlobalBounds().height)));
}

Ball::Ball()
{

}

Ball::Ball(const sf::RenderWindow* window, int type)
	: _type(type)
{
	initShape(window);
}

Ball::~Ball()
{

}

const sf::CircleShape & Ball::getShape() const
{
	return _shapeEnemy;
}

const int & Ball::getType() const
{
	return _type;
}

void Ball::update()
{

}

void Ball::render(sf::RenderTarget * target)
{
	target->draw(_shapeEnemy);
}
