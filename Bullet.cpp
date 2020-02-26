#include "Bullet.h"

Bullet::Bullet(sf::Vector2f startingCoordinate, sf::Vector2f direction, float velocity, float damagePoints)
{
	coordinate=(startingCoordinate);
	this->direction = direction;
	this->damagePoints = damagePoints;
	this->velocity = velocity;
}


void Bullet::update(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
	coordinate.x += direction.x*velocity * deltaTime.asSeconds();
	coordinate.y += direction.y*velocity * deltaTime.asSeconds();
	body.setPosition(coordinate);
	
}

void Bullet::draw(sf::RenderWindow& window)
{
	body.setSize(sf::Vector2f(10.f,10.f));
	body.setFillColor(sf::Color(255, 0, 0, 255));
	window.draw(body);
}
