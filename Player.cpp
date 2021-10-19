#include "Player.h"

void Player::initVariables()
{
	_movementSpeed			= 5.f;
	_hpMax					= 10;
	_hp						= _hpMax;
}

void Player::initShape()
{
	_shape.setFillColor(sf::Color::Green);
	_shape.setSize(sf::Vector2f(30.f, 30.f));

}

													// Construction
Player::Player(float x, float y)
{
	_shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

													// Destruction
Player::~Player()
{

}

													// Accessor
const sf::RectangleShape & Player::getShape() const
{
	return _shape;
}

const int & Player::getHp() const
{
	return _hp;
}

const int & Player::getHpMax() const
{
	return _hpMax;
}

void Player::makeDamage(const int damage)
{
	if (_hp > 0)
		_hp -= damage;

	if (_hp <= 0)
		_hp = 0;
}

void Player::gainHealth(const int health)
{
	if (_hp < _hpMax)
		_hp += health;

	if (_hp > _hpMax)
		_hp = _hpMax;
}

													// Function
void Player::updateInput()
{
													// Keyboard input
													// Left movements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_shape.move((-_movementSpeed), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_shape.move((_movementSpeed), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_shape.move(0.f, (-_movementSpeed));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_shape.move(0.f, (_movementSpeed));
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
													// Left
	if (_shape.getGlobalBounds().left <= 0.f)
	{
		_shape.setPosition(0.f, _shape.getGlobalBounds().top);
	}
													// Right
	if (_shape.getGlobalBounds().left + _shape.getGlobalBounds().width >= target->getSize().x)
	{
		_shape.setPosition(target->getSize().x - _shape.getGlobalBounds().width, _shape.getGlobalBounds().top);
	}
													// Top
	if (_shape.getGlobalBounds().top <= 0.f)
	{
		_shape.setPosition(_shape.getGlobalBounds().left, 0.f);
	}
													// Bottom
	if (_shape.getGlobalBounds().top + _shape.getGlobalBounds().height >= target->getSize().y)
	{
		_shape.setPosition(_shape.getGlobalBounds().left, target->getSize().y - _shape.getGlobalBounds().height);
	}
}

void Player::update(const sf::RenderTarget * target)
{
	this->updateInput();

													// Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget * target)
{
	target->draw(_shape);
}
