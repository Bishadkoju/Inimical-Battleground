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
	sf::Vector2f mouseDirection;
	sf::Vector2f coordinate;
	sf::Vector2f currentVelocity;
	sf::Vector2f targetVelocity;
	sf::Time deltaTime;
	sf::Vector2f maxGroundVelocity;
	sf::Vector2f maxAirVelocity;
	sf::RectangleShape body;
	float groundDampingConstant;
	float airDampingConstant;
	float gravity;
	float elasticConstant;
	float thrustValue;
	bool isOnGround;
	sf::RectangleShape bar;
	sf::RectangleShape arena_blocks[2];
	
	bool facingRight, facingLeft;
	sf::VideoMode window;
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

	void handlePlayerCollision(sf::RectangleShape other);
	void evaluateMouseDirection(sf::RenderWindow& window);
	void movePlayer(sf::Vector2f maxVelocity, float dampingConstant);
	
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
	void getUserInput( );
	Collider *collider;
	Collider getCollider();
	sf::Vector2f getCoordinate();
	sf::Vector2f getVelocity();
	float interpolateVelocity(float target,float current,float dampingFactor);
	void draw(sf::RenderWindow& window);
};

