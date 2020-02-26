#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include"Player.h"
class Game
{
protected:
	Player p;
	sf::RenderWindow window;
	int m_width, m_height;
	sf::Texture texture, brick;
	sf::Sprite sprite;
	sf::CircleShape shape;
	
public:
	Game(int width,int height);
	void run();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();
	void update(sf::Time);
	void render();
	void collision();
};

