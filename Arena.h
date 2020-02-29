#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
class Arena
{
public:
	static const int noOfBlocks=4;
	sf::RectangleShape blocks[noOfBlocks];
	//sf::Vector2f sizes[noOfBlocks], positions[noOfBlocks];
	sf::Vector2f sizes[noOfBlocks] = {sf::Vector2f(100,50),sf::Vector2f(100,50),sf::Vector2f(500, 50) };
	sf::Vector2f positions[noOfBlocks] = { sf::Vector2f(300,200),sf::Vector2f(900,500) ,sf::Vector2f(0,500) };
	Arena();
	void draw(sf::RenderWindow &window);
	sf::Texture textureBackImag;
	sf::Sprite spriteBackGroundImage;
	
};

