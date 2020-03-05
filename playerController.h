#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
class playerController
{
public:
	bool isPressedLeft, isPressedRight, isPressedUp;
	bool isLeftMouseButtonPressed, isRightMouseButtonPressed;
	sf::Vector2f mousePosition;
	playerController(bool isPressedLeft, bool  isPressedRight, bool isPressedUp,
		bool isLeftMouseButtonPressed, bool isRightMouseButtonPressed, sf::Vector2f mousePosition);
	playerController() {}
};

