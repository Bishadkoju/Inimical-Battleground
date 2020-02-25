#include "Collider.h"

Collider::Collider(sf::RectangleShape& body):body(body){}

bool Collider::checkCollision(Collider other)
{
	return body.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::FloatRect Collider::getGlobalBounds()
{
	return this->body.getGlobalBounds();
}



