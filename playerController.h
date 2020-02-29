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

};

