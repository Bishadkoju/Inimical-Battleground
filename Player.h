#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<cmath>
#include "Collider.h"
#include "Animation.h"

class Player
{
private:
	sf::Vector2f coordinate;
	sf::Vector2f currentVelocity;
	sf::Vector2f targetVelocity;
	sf::Time deltaTime;
	sf::Vector2f maxGroundVelocity;
	sf::Vector2f maxAirVelocity;
	sf::RectangleShape body;
	sf::VideoMode window;
	float groundDampingConstant;
	float airDampingConstant;
	float gravity;
	float elasticConstant;
	float thrustValue;
	sf::RectangleShape bar;
	bool isOnGround;
	bool facingRight, facingLeft;
	sf::Texture texture;
	sf::Texture* ptexture;
	sf::Texture lhand, rhand;
	sf::Sprite spritePlayer, playerHandLeft, playerHandRight;

	enum class AnimationIndex
	{
		walkingleft,
		flyingleft,
		walkingright,
		flyingright,
		standing,
		maxCount
	};
	Animation animations[int(AnimationIndex::maxCount)];
	AnimationIndex curAnimation = AnimationIndex::walkingright;
	bool noKeyWasPressed;


public:
	bool isPressedUp, isPressedLeft, isPressedRight,isCollided;
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosition;
	sf::Vector2f aimDirNorm;
	sf::Vector2f aimDir;
	void setBulletDir(sf::RenderWindow& window);
	Player();
	
	void update(sf::Time);
	void setCoordinate(sf::Vector2f);
	void setCoordinate(float x, float y);
	void setXVelocity(int,bool);
	void getUserInput( );
	Collider getCollider();
	sf::Vector2f getCoordinate();
	sf::Vector2f getVelocity();
	float interpolateVelocity(float target,float current,float dampingFactor);
	void draw(sf::RenderWindow& window);
};

