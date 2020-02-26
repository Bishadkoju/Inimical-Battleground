#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class Bullet
{
private:
	sf::Vector2f direction;
	float velocity;
	float damagePoints;
	sf::Time deltaTime;
	sf::Vector2f coordinate;
	
public:
	Bullet(sf::Vector2f startingCoordinate,sf::Vector2f direction,float velocity,float damagePoints);
	sf::RectangleShape body;
	void setDirection(sf::Vector2f direction);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

};

