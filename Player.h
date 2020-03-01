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
#include "Bullet.h"
#include "Arena.h";
#include "playerController.h"
class Player
{
private:

	

	// Physics Related Stuffs
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
	float fuel = 1000;

	std::vector<Bullet> bullets;
	sf::Clock bulletClock;
	
	// Render Related
	bool facingRight;
	sf::VideoMode window;
	sf::Texture texture;
	sf::Texture* ptexture;
	sf::Texture lhand, rhand;
	sf::Sprite spritePlayer, playerHandLeft, playerHandRight;
	float scale;

	Arena *arena1;

	enum class AnimationIndex
	{
		walkingleft,
		flyingleft,
		walkingright,
		flyingright,
		standingright,
		standingleft,
		maxCount
	};

	Animation animations[int(AnimationIndex::maxCount)];
	AnimationIndex curAnimation = AnimationIndex::walkingright;
	bool noKeyWasPressed;


	void handlePlayerCollision(sf::RectangleShape other);
	void movePlayer(sf::Vector2f maxVelocity, float dampingConstant);
	
public:
	sf::Vector2f mouseDirection;
	sf::Vector2f mousePosition;
	bool isPressedUp, isPressedLeft, isPressedRight,isCollided;
	bool isLeftMouseButtonPressed,isRightMouseButtonPressed;
	
	sf::Vector2f playerCenter;
	
	int totalBullets;
	int bulletsPerRoundMaximum;
	int bulletsOnRound;
	sf::Clock reloadClock;
	bool isReloading;
	

	void setBulletDir();
	Player();
	void update(sf::Time,playerController userController);
	void setCoordinate(sf::Vector2f);
	void setCoordinate(float x, float y);

	Collider *collider;
	Collider getCollider();
	sf::Vector2f getCoordinate();
	sf::Vector2f getVelocity();
	float interpolateVelocity(float target,float current,float dampingFactor);
	void draw(sf::RenderWindow& window);
	void setArena(Arena& arena);
};

