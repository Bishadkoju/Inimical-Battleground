#include "playerController.h"

playerController::playerController(bool isPressedLeft, bool isPressedRight, bool isPressedUp, bool isLeftMouseButtonPressed, bool isRightMouseButtonPressed, sf::Vector2f mousePosition)
{
	this->isPressedLeft = isPressedLeft;
	this->isPressedRight = isPressedRight;
	this->isPressedUp=isPressedUp;
	this->isLeftMouseButtonPressed = isLeftMouseButtonPressed;
	this->isRightMouseButtonPressed=isRightMouseButtonPressed;
	this->mousePosition= mousePosition;
}
