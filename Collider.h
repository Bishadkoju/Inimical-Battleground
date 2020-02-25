#pragma once
#include <SFML/Graphics.hpp>
class Collider
{
public:
	Collider(sf::RectangleShape& body);
	bool checkCollision(Collider other);
	sf::FloatRect getGlobalBounds();

private:
	sf::RectangleShape &body;
};

